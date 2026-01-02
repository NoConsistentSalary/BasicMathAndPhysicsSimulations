#include <stdio.h>
#include <mikroplot/window.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <tuple>

glm::vec2 rotatePoint(float angle, const glm::vec2& point)
{
	auto matRot = glm::rotate(glm::mat4(1.0), angle, glm::vec3(0, 0, 1));
	auto pointRotated = matRot * glm::vec4(point.x, point.y, 0.0f, 1.0f);
	return glm::vec2(pointRotated.x, pointRotated.y);
}

struct Sphere
{
	glm::vec2 position;
	float radius;
	float angle = 0.0f;
	bool collides = false;
	glm::vec2 velocity;

	void render(mikroplot::Window &window) const
	{
		if (collides)
		{
			window.drawCircle({ position.x,position.y }, radius,8);
		}
		else
		{
			window.drawCircle({ position.x,position.y }, radius);
		}

		auto p1 = rotatePoint(angle,glm::vec2(radius, 0)) + position;
		auto p0 = rotatePoint(angle, glm::vec2(-radius, 0)) + position;
		window.drawLines({ {p1.x,p1.y},{p0.x,p0.y} },11);
		
	}

};

struct AABB
{
	glm::vec2 position;
	glm::vec2 halfSize;
	bool collides = false;

	glm::vec2 getSize() const
	{
		return 2.0f * halfSize;
	}

	auto getVertices() const
	{
		std::vector<mikroplot::vec2> res;
		res.push_back({position.x + halfSize.x, position.y + halfSize.y});
		res.push_back({ position.x - halfSize.x, position.y + halfSize.y });
		res.push_back({ position.x - halfSize.x, position.y - halfSize.y });
		res.push_back({ position.x + halfSize.x, position.y - halfSize.y });
		res.push_back({ position.x + halfSize.x, position.y + halfSize.y });

		return res;
	}

	void render(mikroplot::Window& window) const
	{
		auto vertices = getVertices();

		if(collides)
			window.drawLines(vertices,8);
		else
			window.drawLines(vertices);
	}
};

typedef std::tuple<bool, glm::vec2, glm::vec2> ContactManifold;

//contact manifold
ContactManifold hasCollision(const Sphere & objA, const Sphere& objB)
{
	auto vecD = objB.position - objA.position;
	float d = glm::length(vecD);
	float totalR = objA.radius + objB.radius;

	bool collides = d < totalR;
	if (collides)
	{
		glm::vec2 collisionPointA = objA.position + objB.radius * glm::normalize(vecD);
		glm::vec2 collisionNormalA = glm::normalize(-vecD);
		return std::make_tuple(true, collisionPointA, collisionNormalA);
	}

	return std::make_tuple(false, glm::vec2(0), glm::vec2(0));
}

bool hasCollisionOptim(const Sphere& objA, const Sphere& objB)
{
	auto vecD = objA.position - objB.position;
	float dpow2 = dot(vecD,vecD);
	float totalR = objA.radius + objB.radius;
	//d^2 < (r1+r2)
	return dpow2 < totalR*totalR;
}


bool hasCollision(const AABB& objA, const AABB& objB)
{
	float dPosX = abs(objB.position.x - objA.position.x);
	float halSizeSumX = objA.halfSize.x + objB.halfSize.x;

	float dPosY = abs(objB.position.y - objA.position.y);
	float halSizeSumY = objA.halfSize.y + objB.halfSize.y;

	return dPosX < halSizeSumX && dPosY < halSizeSumY;
}

void JOTAHIN()
{
	//laske tormayspisteet ja normaait nelikulmioille
	//peiliheijastuksen kaavan johtaminen
	//inside peliohjelmointi by andre...
}

glm::vec2 reflect(const glm::vec2& r, const glm::vec2& N)
{
	return r - 2.0f * dot(r,N) * N;
}

int main()
{

	std::vector<Sphere> spheres;
	std::vector<AABB> aabbs;

#if 1
	spheres.push_back(Sphere{ glm::vec2(0,0),0.5f });
	spheres.push_back(Sphere{ glm::vec2(3,0),1.0f });
	spheres.push_back(Sphere{ glm::vec2(-3,3),1.5f });
#else
	aabbs.push_back(AABB{ glm::vec2(0.0f,0.0f) ,glm::vec2(0.5f,0.5f) });
	aabbs.push_back(AABB{ glm::vec2(3.0f,0.0f) ,glm::vec2(0.75f,0.5f) });
	aabbs.push_back(AABB{ glm::vec2(-3.0f,3.0f) ,glm::vec2(1.5f,1.0f) });
#endif

	spheres[1].velocity.x = -0.8f;
	spheres[1].velocity.y = 0.3f;
	spheres[1].velocity *= 5;

	spheres[2].velocity.x = 1.0;
	spheres[2].velocity.y = -1.0;
	spheres[2].velocity *= 2;

	mikroplot::Window window(800, 800, "AABB collisions");
	mikroplot::Timer timer;
	while (false == window.shouldClose())
	{

		int left = window.getKeyState(mikroplot::KeyCodes::KEY_LEFT);
		int right = window.getKeyState(mikroplot::KeyCodes::KEY_RIGHT);
		int up = window.getKeyState(mikroplot::KeyCodes::KEY_UP);
		int down = window.getKeyState(mikroplot::KeyCodes::KEY_DOWN);

		float dx = right - left;
		float dy = up - down;

		float deltatime = timer.getDeltaTime();

		/*aabbs[0].position.x += dx * deltatime;
		aabbs[0].position.y += dy * deltatime;*/
#if 1
		spheres[0].position.x += dx * deltatime;//*deltatime
		spheres[0].position.y += dy * deltatime;

		for (auto& obj : spheres)
		{
			obj.position += obj.velocity * deltatime;
		}

		for (size_t i = 0; i < spheres.size(); i++)
		{
			spheres[i].collides = false;
		}

		for (size_t i = 0; i < spheres.size(); i++)
		{
			const auto & objA = spheres[i];

			if (objA.position.x < -10.0f || objA.position.x > 10.0f)
			{
				spheres[i].velocity.x *= -1;
			}

			if (objA.position.y < -10.0f || objA.position.y > 10.0f)
			{
				spheres[i].velocity.y *= -1;
			}

			//alussa j+1 koska aloitetaan vertaamoinen seuraavasta obkektista alkaen
			//yksipuolinen collision check
			for (size_t j = i+1; j < spheres.size();j++)
			{
				const auto& objB = spheres[j];
				//if (i == j) continue;
				ContactManifold manifold = hasCollision(objA, objB);
				const auto& [collides, contactPoint, contactNormal] = manifold;

				if(collides)
				{
					printf("posAX: %2.2f\nposAY: %2.2f\nCAX: %2.2f\nCAY: %2.2f\nNAX: %2.2f\nNAY: %2.2f\n\n",
						objA.position.x, objA.position.y, contactPoint.x, contactPoint.y, contactNormal.x, contactNormal.y);

				spheres[i].collides = true;
				spheres[j].collides = true;

				window.drawLines({
					{contactPoint.x,contactPoint.y},
					{contactPoint.x + 0.5f*contactNormal.x,contactPoint.y + 0.5f * contactNormal.y}
					});

				}

				spheres[i].velocity = reflect(objA.velocity, contactNormal);
				spheres[j].velocity = reflect(objB.velocity, -contactNormal);
			}

		}
#endif

		//for (size_t i = 0; i < aabbs.size(); i++)
		//{
		//	aabbs[i].collides = false;
		//}

		//for (size_t i = 0; i < aabbs.size(); i++)
		//{
		//	const auto& objA = aabbs[i];

		//	//alussa j+1 koska aloitetaan vertaamoinen seuraavasta obkektista alkaen
		//	//yksipuolinen collision check
		//	for (size_t j = i + 1; j < aabbs.size(); j++)
		//	{
		//		const auto& objB = aabbs[j];
		//		//if (i == j) continue;
		//		bool collides = hasCollision(objA, objB);

		//		if (collides)
		//		{
		//			aabbs[i].collides = true;
		//			aabbs[j].collides = true;
		//		}
		//	}
		//}

		window.setScreen(-10, 10, -10, 10);
		window.drawAxis();
		
		for (const auto& sphere : spheres)
		{
			sphere.render(window);
		}

		/*for (const auto& aabb : aabbs)
		{
			aabb.render(window);
		}*/

		window.update();

	}

	return 0;

}