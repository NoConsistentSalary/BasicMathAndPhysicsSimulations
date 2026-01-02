#include <stdio.h>
#include <mikroplot/window.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <tuple>

typedef std::tuple<bool, glm::vec2, glm::vec2> ContactManifold;

//*********************************************************************

class Sphere
{
public:
	Sphere(glm::vec2 pos, float rad, glm::vec2 vel):
		position(pos), radius(rad), velocity(vel)
	{
		calculateMass();
	}

	void update(float deltaTime)
	{
		glm::vec2 g(0, -9.80665f);
		velocity += g * deltaTime;
		position += velocity * deltaTime;
		angle += 0.5 * angularVelocity * deltaTime;
	}

	void render(auto& window)
	{
		if (collides)
		{
			window.drawCircle({ position.x,position.y }, radius, 8);
		}
		else
		{
			window.drawCircle({ position.x,position.y }, radius);
		}

		glm::vec2 p1 = rotatePoint(angle, glm::vec2(radius, 0)) + position;
		glm::vec2 p0 = rotatePoint(angle, glm::vec2(-radius, 0)) + position;
		window.drawLines({ {p1.x,p1.y},{p0.x,p0.y} }, 11);
	}

	//	Setters
	void set_collides(bool col) { collides = col; }
	void set_position(glm::vec2 pos) { position = pos; }
	void set_radius(float rad) { radius = rad; }
	void set_angle(float ang) { angle = ang; }
	void set_velocity(glm::vec2 vel) { velocity = vel; }
	void set_mass(float mas) { mass = mas; }
	void set_angular_velocity(float angvel) { angularVelocity = angvel; }

	//	Getters
	bool get_collides() const { return collides; }
	glm::vec2 get_position() const { return position; }
	glm::vec2 get_velocity() { return velocity; }
	float get_radius() const { return radius; }

	//	Direction changing
	void chainge_x_dir() { velocity.x *= -1.0f; }
	void chainge_y_dir() { velocity.y *= -1.0f; }

private:

	float getMomentOfInteria() const
	{
		return mass * radius * radius * 2.0f / 5.0f;
	}

	glm::vec2 rotatePoint(float angle, glm::vec2 point)
	{
		auto matRot = glm::rotate(glm::mat4(1.0), angle, glm::vec3(0, 0, 1));
		auto pointRotated = matRot * glm::vec4(point.x, point.y, 0.0f, 1.0f);
		return glm::vec2(pointRotated.x, pointRotated.y);
	}

	void calculateMass()
	{
		mass = 3.14159265f * radius * radius;
	}

	glm::vec2 position;
	float radius;
	float angle = 0.0f;
	bool collides = false;
	glm::vec2 velocity;
	float mass = 1.0f;
	float angularVelocity = 0.0f;
};

//*********************************************************************

class System
{
public:
	System(glm::vec2 bounds):system_boundaries(bounds)
	{}

	void add_sphere(Sphere sphere)
	{
		spheres.push_back(sphere);
	}

	void update(float deltatTime)
	{
		if (spheres.size())
		{
			checkCollisions();

			for (Sphere &sphere : spheres)
			{
				sphere.update(deltatTime);
			}

			resetCollisions();
		}
	}

	void render(auto& window)
	{
		if (spheres.size())
		{
			for (Sphere sphere : spheres)
			{
				sphere.render(window);
			}
		}

		if (contactpoints.size())
		{
			for (ContactLifetime i : contactpoints)
			{
				const auto& [collides, contactPoint, contactNormal] = i.manifold;

				window.drawLines({
					{contactPoint.x,contactPoint.y},
					{contactPoint.x + 0.5f * contactNormal.x,contactPoint.y + 0.5f * contactNormal.y}
					}, 8);
			}
			updateContacts();
		}
	}

private:

	//
	void checkCollisions()//const
	{
		if (spheres.size())
		{
			for (size_t i = 0; i < spheres.size(); i++)
			{
				Sphere& objA = spheres[i];

				checkBoundaries(objA);

				for (size_t j = i + 1; j < spheres.size(); j++)
				{
					Sphere& objB = spheres[j];

					ContactManifold manifold = hasCollision(objA, objB);

					const auto& [collides, contactPoint, contactNormal] = manifold;

					if (collides)
					{
						spheres[i].set_collides(true);
						spheres[j].set_collides(true);

						contactpoints.push_back(ContactLifetime(manifold, 30));
					}

					spheres[i].set_velocity(reflect(objA.get_velocity(), contactNormal));
					spheres[j].set_velocity(reflect(objB.get_velocity(), -contactNormal));
				}
			}
		}
	}

	//
	ContactManifold hasCollision(const Sphere& objA, const Sphere& objB)
	{
		auto vecD = objB.get_position() - objA.get_position();
		float d = glm::length(vecD);
		float totalR = objA.get_radius() + objB.get_radius();

		bool collides = d < totalR;
		if (collides)
		{
			glm::vec2 collisionPointA = objA.get_position() + objB.get_radius() * glm::normalize(vecD);
			glm::vec2 collisionNormalA = glm::normalize(-vecD);
			return std::make_tuple(true, collisionPointA, collisionNormalA);
		}

		return std::make_tuple(false, glm::vec2(0), glm::vec2(0));
	}

	//
	bool hasCollisionOptim(const Sphere& objA, const Sphere& objB)
	{
		auto vecD = objA.get_position() - objB.get_position();
		float dpow2 = dot(vecD, vecD);
		float totalR = objA.get_radius() + objB.get_radius();
		//d^2 < (r1+r2)
		return dpow2 < totalR * totalR;
	}

	//
	void resetCollisions()
	{
		if (spheres.size())
		{
			for (Sphere &sphere : spheres)
			{
				sphere.set_collides(false);
			}
		}
	}

	//check out of bounds objects and bounce them back
	void checkBoundaries(Sphere& obj) const
	{
		if ((obj.get_position().x - obj.get_radius()) <= -system_boundaries.x ||
			(obj.get_position().x + obj.get_radius()) >= system_boundaries.x)
		{
			float dif = 0.0f;

			//left side
			if ((obj.get_position().x - obj.get_radius()) < -system_boundaries.x)
			{
				dif = (obj.get_position().x - obj.get_radius()) + system_boundaries.x;
				glm::vec2 newpos = obj.get_position();
				newpos.x -= dif;
				obj.set_position(newpos);
			}
			//right side
			if((obj.get_position().x + obj.get_radius()) > system_boundaries.x)
			{
				dif = (obj.get_position().x + obj.get_radius()) - system_boundaries.x;
				glm::vec2 newpos = obj.get_position();
				newpos.x -= dif;
				obj.set_position(newpos);
			}

			obj.chainge_x_dir();
		}

		if ((obj.get_position().y - obj.get_radius()) <= -system_boundaries.y ||
			(obj.get_position().y + obj.get_radius()) >= system_boundaries.y)
		{
			float dif = 0.0f;

			//down side
			if ((obj.get_position().y - obj.get_radius()) < -system_boundaries.y)
			{
				dif = (obj.get_position().y - obj.get_radius()) + system_boundaries.y;
				glm::vec2 newpos = obj.get_position();
				newpos.y -= dif;
				obj.set_position(newpos);
			}
			//up side
			if ((obj.get_position().y + obj.get_radius()) > system_boundaries.y)
			{
				dif = (obj.get_position().y + obj.get_radius()) - system_boundaries.y;
				glm::vec2 newpos = obj.get_position();
				newpos.y -= dif;
				obj.set_position(newpos);
			}

			obj.chainge_y_dir();
		}
		
	}

	//Reflect the ball direction
	glm::vec2 reflect(const glm::vec2& r, const glm::vec2& N)
	{
		return r - 2.0f * dot(r, N) * N;
	}

	//
	void updateContacts()
	{
		for (size_t i = 0; i < contactpoints.size(); i++)
		{
			if(contactpoints[i].lifetime)
			{
				contactpoints[i].lifetime--;
				printf("1\n");
			}
			else
			{
				contactpoints.pop_back();
				printf("0\n");
			}
		}
	}

	struct ContactLifetime
	{
		ContactManifold manifold;
		int lifetime;
	};

	std::vector<Sphere> spheres;
	std::vector<ContactLifetime> contactpoints;

	glm::vec2 system_boundaries;
};

//*********************************************************************

int main()
{
	mikroplot::Window window(800, 800, "Collisions with mass");
	mikroplot::Timer timer;

	System system(glm::vec2({10,10}));

	//pos rad vel
	Sphere sphere0(glm::vec2(0,0), 1.0f, glm::vec2(0));
	Sphere sphere1(glm::vec2(4,3), 0.5f, glm::vec2(0));
	Sphere sphere2(glm::vec2(-4,3), 0.5f, glm::vec2(4,0));

	Sphere sphere3(glm::vec2(0,-9.8), 0.6f, glm::vec2(0.-1));

	system.add_sphere(sphere0);
	system.add_sphere(sphere1);
	system.add_sphere(sphere2);

	//system.add_sphere(sphere3);


	while (false == window.shouldClose())
	{
		float deltatime = timer.getDeltaTime();

		system.update(deltatime);

		window.setScreen(-10, 10, -10, 10);
		window.drawAxis();

		system.render(window);

		window.update();
	}

	return 0;
}

/*	Palautustiedosto: submissions/t7/collision_demo.cpp

 - Liikem��r�: p = mv, Voima: F=dp/dt, Impulssi: I = Ft (1 p)			Juu?

 - Lineaarinen t�rm�ys: v_a1 = v_a0 + n(j/M_a) ja v_b1 = v_b0 - n(j/M_b), miss� j:n kaava l�ytyy Heckerin artikkelista 3, kaava 6 (1 p)  juu?
 
 - Tee demo, jossa kaksi pallomaista (sphere collision) partikkelia t�rm�� toisiinsa. (1 p)			juu

 - Tee ensin t�rm�ykset niin, ett� oletat objektien massan samaksi. (1 p)				joo?

 - Kun sama massaisten t�rm�ys toimii, lis�� toiminnallisuus, joka ottaa massan huomioon. (1 p)			juu
*/


/*			More ideas:
 - ...
*/