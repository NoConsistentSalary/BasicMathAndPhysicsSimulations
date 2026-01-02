#pragma once
#include "mikroplot/window.h"
#include <glm/gtc/matrix_transform.hpp>
#include "gameobject.h"

namespace cardemo
{

	class Car : public GameObject
	{
	public:
		Car() : GameObject()
		{}

		Car(glm::vec2 pos, glm::vec2 sca, float rot) : GameObject(pos, sca, rot)
		{}

		virtual ~Car()
		{}

		void Render(mikroplot::Window &window)
		{
			if(collides)
				window.drawLines(getVertices(), 8);
			else
				window.drawLines(getVertices(), 10);

			//draw the car as rectangle
			window.drawLines({ glm_to_mikroplot(position),glm_to_mikroplot(position + forwardVec) }, 8);
			//draw forwardvec point
			window.drawPoints({ glm_to_mikroplot(position + forwardVec) }, 8, 5);

			//draw centetr lines to indicate cars forward direction and movement direction
			window.drawLines({ glm_to_mikroplot(glm::vec2({0.0f,0.0f})),glm_to_mikroplot(velocity * 10.0f)}, 8,5);
			window.drawLines({ glm_to_mikroplot(glm::vec2({0.0f,0.0f})),glm_to_mikroplot(forwardVec * 10.0f) }, 4);
		}


		void Update(float deltaTime)
		{
			const float rotationSpeed = 2.0f;		//rotational speed
			const float movementSpeed = 0.7f;		//movement speed
			const float airResistance = 0.1f;		//air resistance
			const float tireDamper = 0.9999f;		//tire dampning force
			const float dampning = 3.0f;			//extra dampning

			//calculate angular velocity
			angularVelocity = rotationSpeed * rotationInput;

			//create forward vector so speed is always applied to the right direction
			forwardVec = glm::normalize(rotatePoint(rotation, glm::vec2({ 0,1 })));

			//calculate basic movement force
			glm::vec2 movement = forwardVec * movementInput * movementSpeed;
			velocity += movement;
			
			//apply resistance forces when velocity increases
			if (glm::dot(velocity, velocity) > 0.001f)
			{
				//calculate air resistanse force, scale it with deltatime and apply it to velocity
				glm::vec2 airResistanceForce = -glm::normalize(velocity) * glm::dot(velocity, velocity) * airResistance;
				velocity += airResistanceForce * deltaTime;
				
				glm::vec2 velocityInCarCoordinates = rotatePoint(-rotation, velocity);

				//velocityInCarCoordinates.y *= tireDamper;
				//velocityInCarCoordinates.x *= tireDamper;
				velocityInCarCoordinates *= tireDamper;

				velocity = rotatePoint(rotation, velocityInCarCoordinates);

				//printf("%f\n", angularVelocity);
			}

			//count acceleration
			glm::vec2 acceleration = velocity / mass;

			//scale forces with deltatime
			acceleration *= deltaTime;
			angularVelocity *= deltaTime;

			//apply forces
			move(acceleration);
			rotate(angularVelocity);

			//dampning so that acceleration goes down faster after throttle is let go.
			velocity *= (1.0f - deltaTime * dampning);
		}




		void moveCar(float speed)
		{
			velocity += speed;
		}

		void moveCar(glm::vec2 speed)
		{
			velocity += speed;
		}

		void rotateCar(float speed)
		{
			angularVelocity += speed;
		}



		glm::vec2 getForward()
		{ return forwardVec; }

		std::vector<glm::vec2> calculateEdgeNormals()
		{
			std::vector<glm::vec2> normals;

			std::vector<mikroplot::vec2> mvertices = getVertices();
			std::vector<glm::vec2> vertices = convertVertices(mvertices);


			for (size_t i = 0; i < vertices.size() - 1; ++i) {
				glm::vec2 edge = vertices[i + 1] - vertices[i];
				glm::vec2 normal = glm::normalize(glm::vec2(-edge.y, edge.x));
				normals.push_back(normal);
			}

			return normals;
		}

		std::vector< mikroplot::vec2 > getVertices()
		{
			std::vector<mikroplot::vec2> vertices =
			{
				mikroplot::vec2(halfsize.x, halfsize.y),
				mikroplot::vec2(-halfsize.x, halfsize.y),
				mikroplot::vec2(-halfsize.x, -halfsize.y),
				mikroplot::vec2(halfsize.x, -halfsize.y),
				mikroplot::vec2(halfsize.x, halfsize.y),//Onko turhaa?
			};

			glm::mat4 model = getModelMatrix();
			for (mikroplot::vec2& p : vertices)
			{
				glm::vec4 newP = model * glm::vec4(p.x, p.y, 0, 1);//w paikalle pitaa tulla 1
				p.x = newP.x;
				p.y = newP.y;
			}

			return vertices;
		}

		glm::mat4 getModelMatrix()
		{
			glm::mat4 matRot = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0, 0, 1));
			glm::mat4 matTrans = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));
			glm::mat4 matModel = matTrans * matRot;
			return matModel;
		}



		std::pair<float, float> project(const glm::vec2& axis)
		{
			std::vector< glm::vec2 > vertices = convertVertices(getVertices());

			float min = std::numeric_limits<float>::max();
			float max = std::numeric_limits<float>::lowest();

			for (const glm::vec2& vertex : vertices) {
				float projection = glm::dot(vertex, axis);
				min = std::min(min, projection);
				max = std::max(max, projection);
			}

			return { min, max };
		}

		//setters and getters

		void set_collides(bool coll) { collides = coll; }

		float get_mass() { return mass; }

		glm::vec2 get_velocity() { return velocity; }

		void set_velocity(glm::vec2 v) { velocity = v; }

		void set_rotationInput(float ri) { rotationInput = ri; }
		void set_movementInput(float mi) { movementInput = mi; }

	private:

		

		bool collides = false;

		const glm::vec2 halfsize = { 0.4f, 1.2f };
		glm::vec2 velocity = { 0.0f, 0.0f };

		glm::vec2 forwardVec = { 0.0f, 0.0f };

		float rotationInput = 0.0f;
		float movementInput = 0.0f;

		//glm::vec2 sumVec = { 0.0f, 0.0f };

		float mass = 1.0f;
		float angularVelocity = 0.0f;

		//mikroplot::Texture texture;
	};

	//****************************************************************************************************
	//****************************************************************************************************

	class AICar : public Car
	{
	public:

		AICar() : Car()
		{
			;
		}

		~AICar()
		{
			;
		}

	private:
	};

}
