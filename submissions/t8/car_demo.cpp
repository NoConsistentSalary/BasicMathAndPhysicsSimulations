#include "mikroplot/window.h"
#include "car.h"

class Application
{
public:
	Application(int xsiz, int ysiz, std::string name):
		window(xsiz,ysiz,name)
	{
		deltaTime = timer.getDeltaTime();
		window.setClearColor(9);

		//Wall initializations
		{

			/*
				The walls are rotated so that their normals are blocking
				the palyer correctly.
			*/

			/*		OuterWalls		*/

			//Righ wall
			Wall w0;
			w0.position = glm::vec2({ 26, 0 });
			w0.rotDeg = 0.0;

			//Left wall
			Wall w1;
			w1.position = glm::vec2({ -26,0 });
			w1.rotDeg = 180.0;

			//Up wall
			Wall w2;
			w2.position = glm::vec2({ 0,24 });
			w2.rotDeg = 90.0;

			//Down wall
			Wall w3;
			w3.position = glm::vec2({ 0,-24 });
			w3.rotDeg = -90.0;

			/*		InnerWalls		*/

			//Righ wall
			Wall w4;
			w4.position = glm::vec2({ 9, 0 });
			w4.rotDeg = 180.0;
			w4.lineLenght = 9.0f;

			//Left wall
			Wall w5;
			w5.position = glm::vec2({ -9,0 });
			w5.rotDeg = 0.0;
			w5.lineLenght = 9.0f;

			//Up wall
			Wall w6;
			w6.position = glm::vec2({ 0,9 });
			w6.rotDeg = -90.0;
			w6.lineLenght = 9.0f;

			//Down wall
			Wall w7;
			w7.position = glm::vec2({ 0,-9 });
			w7.rotDeg = 90.0;
			w7.lineLenght = 9.0f;

			/*		Corner Walls		*/

			//Righ wall
			Wall corner0;
			corner0.position = glm::vec2({ 23, 22 });
			corner0.rotDeg = 45.0;
			corner0.lineLenght = 9.0f;

			//Left wall
			Wall corner1;
			corner1.position = glm::vec2({ -23, 22 });
			corner1.rotDeg = 135.0;
			corner1.lineLenght = 9.0f;

			//Up wall
			Wall corner2;
			corner2.position = glm::vec2({ -23, -22 });
			corner2.rotDeg = -135.0;
			corner2.lineLenght = 9.0f;

			//Down wall
			Wall corner3;
			corner3.position = glm::vec2({ 23, -22 });
			corner3.rotDeg = -45.0;
			corner3.lineLenght = 9.0f;

			walls.push_back(w0);
			walls.push_back(w1);
			walls.push_back(w2);
			walls.push_back(w3);

			walls.push_back(w4);
			walls.push_back(w5);
			walls.push_back(w6);
			walls.push_back(w7);

			walls.push_back(corner0);
			walls.push_back(corner1);
			walls.push_back(corner2);
			walls.push_back(corner3);
		}

		//Waypoint initializations
		{
			/*
				Rotationof the waypoints are set so that their normals
				point to the driving direction (aka clockwise)
				..or was it the opposte direction?
			*/

			//Down left waypoint
			Wall wp0;
			wp0.position = glm::vec2({ -15, -16 });
			wp0.rotDeg = -45.0;//-45 -225
			wp0.lineLenght = 12.0f;

			//Up left waypoint
			Wall wp1;
			wp1.position = glm::vec2({ 15, -16 });
			wp1.rotDeg = -315.0;//-135 -315
			wp1.lineLenght = 12.0f;

			//Up right waypoint
			Wall wp2;
			wp2.position = glm::vec2({ 15, 16 });
			wp2.rotDeg = 135.0;//135 315
			wp2.lineLenght = 12.0f;

			//Down right waypoint
			Wall wp3;
			wp3.position = glm::vec2({ -15, 16 });
			wp3.rotDeg = 225.0;//45 225
			wp3.lineLenght = 12.0f;

			waypoints.push_back(wp0);
			waypoints.push_back(wp1);
			waypoints.push_back(wp2);
			waypoints.push_back(wp3);
		}

		player.set_position(glm::vec2({ -12.0f, 0.0f }));
		player.set_velocity(glm::vec2(0));
	}

	~Application()
	{
		;
	}

	void run()
	{
		while (false == window.shouldClose())
		{
			deltaTime = timer.getDeltaTime();

			resetCollisions();

			//get keydata
			float rotDir = window.getKeyState(mikroplot::KeyCodes::KEY_LEFT) - window.getKeyState(mikroplot::KeyCodes::KEY_RIGHT);
			float movDir = window.getKeyState(mikroplot::KeyCodes::KEY_UP) - window.getKeyState(mikroplot::KeyCodes::KEY_DOWN);

			//set the players input
			player.set_movementInput(movDir);
			player.set_rotationInput(rotDir);

			//////////////////////////////////////////////////

			float w = 2.0f * 3.1415f * rotDir;
			w *= 0.8f;

			float speed = 15;
			speed *= movDir;

			glm::vec2 totalforce = cardemo::rotatePoint(player.get_rotation(), glm::vec2(100.0f * movDir, 0));

			player.Update(deltaTime);

			window.setScreen(-30, 30, -30, 30);

			check_wall_collisions();
			check_waypoint_collisions();

			drawWalls(window);
			drawWaypoints(window);

			player.Render(window);

			window.update();

			glm::vec2 vec = player.getForward();
		}
	}

private:

	//---------------------------------------
	//			WallStruct
	//---------------------------------------

	struct Wall
	{
		glm::vec2 position = {0,0};
		//const int pointWidth = 5;

		float rotDeg = 0.0f;
		float lineLenght = 100.0f;
		//const int lineLenght = 300;
		//const int lineWidth = 1;

		//................
		//	Wall functions
		//................

		std::vector<mikroplot::vec2> getVertices()
		{
			glm::vec3 vector({ 0,1,0 });

			glm::vec2 rv = cardemo::rotatePoint(cardemo::degreesToRadians(rotDeg), vector);

			mikroplot::vec2 point1 = cardemo::glm_to_mikroplot(position + (rv * lineLenght));
			mikroplot::vec2 point2 = cardemo::glm_to_mikroplot(position - (rv * lineLenght));

			std::vector<mikroplot::vec2> vertices = {
				point1,
				point2
			};

			return vertices;
		}

		std::vector<glm::vec2> calculateEdgeNormals()
		{
			std::vector<glm::vec2> normals;

			// Saa kulmat, jotka ovat laskettu oikein
			std::vector<mikroplot::vec2> mvertices = getVertices();
			std::vector<glm::vec2> vertices = cardemo::convertVertices(mvertices);

			for (size_t i = 0; i < vertices.size() - 1; ++i) {
				glm::vec2 edge = vertices[i + 1] - vertices[i];
				glm::vec2 normal = glm::normalize(glm::vec2(-edge.y, edge.x)); // Perpendicular
				normals.push_back(normal);
			}

			return normals;
		}

		std::pair<float, float> project(const glm::vec2& axis)
		{
			std::vector< glm::vec2 > vertices = cardemo::convertVertices(getVertices());

			float min = std::numeric_limits<float>::max();
			float max = std::numeric_limits<float>::lowest();

			for (const glm::vec2& vertex : vertices) {
				float projection = glm::dot(vertex, axis);
				min = std::min(min, projection);
				max = std::max(max, projection);
			}

			return { min, max };
		}
	};

	//projectionDir   aka collision dir


	//---------------------------------------
	//			DrawFunctions
	//---------------------------------------

	void drawWalls(mikroplot::Window& window)
	{
		std::vector<mikroplot::vec2> points;
		std::vector<mikroplot::vec2> lines;

		for (Wall w : walls)
		{
			points.push_back( cardemo::glm_to_mikroplot(w.position) );

			window.drawLines(w.getVertices(), 4, 1);
		}
		
		window.drawPoints(points, 4, 5);
	}

	void drawWaypoints(mikroplot::Window& window)
	{
		std::vector<mikroplot::vec2> points;
		std::vector<mikroplot::vec2> lines;

		for (Wall w : waypoints)
		{
			points.push_back(cardemo::glm_to_mikroplot(w.position));

			window.drawLines(w.getVertices(), 11, 1);
		}

		window.drawPoints(points, 11, 5);
	}

	//---------------------------------------
	//			CollisionFunctions
	//---------------------------------------

	float Min(float x, float y)
	{
		return x > y ? y : x;
	}


	//checks any walldata collision with player and return result
	bool check_collisions(Wall& wall, glm::vec2& normal, float& depth)
	{
		auto carVertices = player.getVertices();
		auto wallVertices = wall.getVertices();

		auto carNormals = player.calculateEdgeNormals();
		auto wallNormals = wall.calculateEdgeNormals();

		std::vector<glm::vec2> axes = carNormals;
		axes.insert(axes.end(), wallNormals.begin(), wallNormals.end());

		depth = std::numeric_limits<float>::max(); // Initialize depth at the beginning
		normal = glm::vec2(0); // Initialize normal at the beginning

		for (const auto& axis : axes)
		{
			// Project onto axis     min,max
			auto carProjection = player.project(axis);
			auto wallProjection = wall.project(axis);

			// Check for separation
			if (carProjection.second < wallProjection.first || wallProjection.second < carProjection.first)
			{
				return false; // No collision
			}

			// Calculate axis depth
			float axisDepth = std::min(
				(wallProjection.second - carProjection.first),
				(carProjection.second - wallProjection.first)
			);

			// Update depth and normal if this depth is less
			if (axisDepth < depth)
			{
				depth = axisDepth;
				normal = (carProjection.first < wallProjection.first) ? -axis : axis; // Set normal based on the position
			}
		}

		player.set_collides(true);
		return true;
	}

	//check collision with all walls
	void check_wall_collisions(/*std::vector<bool>& collisionResults*/)
	{
		glm::vec2 normal = glm::vec2(0);
		float depth = 0.0f;

		for (Wall &w : walls) 
		{
			if (check_collisions(w, normal, depth))
			{
				glm::vec2 playerpos = player.get_position();
				playerpos += normal * depth;
				//Move the player to the correct position
				player.set_position(playerpos);
			}
		}

		//printf("wall depth: %f\n", depth);
	}

	//check collision with all waypoints
	void check_waypoint_collisions()
	{
		glm::vec2 normal = glm::vec2(0);
		float depth = 0.0f;

		for (Wall& w : waypoints)
		{
			if (check_collisions(w, normal, depth))
			{
				//No need for waypoint collisions

				/*auto playerpos = player.get_position();
				playerpos += normal * depth;
				player.set_position(playerpos);*/
			}
		}

	}

	void resetCollisions()
	{
		player.set_collides(false);

		if (opponents.size())
		{
			for (cardemo::AICar &ai : opponents)
			{
				ai.set_collides(false);
			}
		}
	}

	//---------------------------------------
	//			Attributes
	//---------------------------------------

	float deltaTime;

	mikroplot::Window window;
	mikroplot::Timer timer;

	cardemo::Car player;

	std::vector<cardemo::AICar> opponents;

	std::vector<Wall> walls;

	std::vector<Wall> waypoints;
};


//******************************************************************
//******************************************************************
//******************************************************************

int main()
{
	Application app(1300, 900, "Car Demo");//2048

	app.run();

	return 0;
}

/*	Palautustiedosto: submissions/t8/car_demo.cpp

 - Tee yksinkertainen 2d-autopelin auton fysiikka tyyliin Slicks 'n slide:
   https://www.youtube.com/watch?v=Elb5L9eRaCw&ab_channel=Nap%27n%27Retrogaming

 - Kaasu, Jarru, V�liaineen vastus (F_kitka = k * v, F_ilma = k * v^2) (1 p)	..

 - Voi menn� sivuluisussa (1 p)													juu

 - K��ntyminen: Joko paikallaan k��ntyv� tai vaihtoehtoisesti k��ntyy ainoastaan vauhdissa.

 - Esimerkki�, josta voi katsoa mallia: https://repo.kamit.fi/mikkorom_examples/opengl_cargame

 - Luento autopelin fysiikasta, jossa kaavat yksinkertaiseen auton fysiikkaan ja lis�ksi esitetty my�s
   monimutkaisempaa mallia: Wassimulator � Programming Vehicles in Games � BSC 2025
   https://www.youtube.com/watch?v=MrIAw980iYg

 - S��d� ohjattavuus niin, ett� autoa on kiva ajaa (1 p)						kait?
*/

