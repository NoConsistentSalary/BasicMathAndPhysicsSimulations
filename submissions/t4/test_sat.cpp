#include "sat.h"

void checkCollision(sat::SAT_Rect& rect1, sat::SAT_Rect& rect2)
{
	std::vector<glm::vec2> normals1 = rect1.calculateEdgeNormals();
	std::vector<glm::vec2> normals2 = rect2.calculateEdgeNormals();

	for (const auto& normal : normals1)
	{
		auto [min1, max1] = rect1.project(normal);
		auto [min2, max2] = rect2.project(normal);

		if (max1 < min2 || max2 < min1)
		{
			return;
		}
	}

	for (const auto& normal : normals2)
	{
		auto [min1, max1] = rect1.project(normal);
		auto [min2, max2] = rect2.project(normal);

		if (max1 < min2 || max2 < min1)
		{
			return;
		}
	}

	rect1.set_collides(true);
	rect2.set_collides(true);
}

void renderRectangles(
	const std::vector<sat::SAT_Rect> &rects, mikroplot::Window &window
)
{
	for (sat::SAT_Rect r : rects)
	{
		std::vector < mikroplot::vec2 > vertices = r.getVertices();

		if(r.get_collides())
			window.drawLines(vertices, 8);
		else
			window.drawLines(vertices, 9);
	}
}

void updateRectangles(
	std::vector<sat::SAT_Rect> &rects, float deltaTime
)
{
	for (size_t i = 0; i < rects.size(); i++)
	{
		for (size_t j = 0; j < rects.size(); j++)
		{
			if (i != j)
			{
				checkCollision(rects[i], rects[j]);
			}
		}
	}
}

void resetCollisions(std::vector<sat::SAT_Rect>& rects)
{
	for (sat::SAT_Rect& r : rects)
	{
		r.set_collides(false);
	}
}




int main()
{
	mikroplot::Window window(800, 800, "SAT collisions");
	mikroplot::Timer timer;

	const float movement_speed = 2.5f;
	const float rotation_speed = 0.5f;

	std::vector<sat::SAT_Rect> rectangles;
	sat::SAT_Rect rec0(glm::vec2(0.0f), glm::vec2(0.5f), 0.0f);
	sat::SAT_Rect rec1(glm::vec2(-3.0f,2.0f), glm::vec2(0.5f,2.0f), 0.0f);
	sat::SAT_Rect rec2(glm::vec2(1.0f, -2.0f), glm::vec2(4.0f,1.0f), 0.0f);
	
	/*rec0.set_collides(true);
	rec1.set_collides(true);
	rec2.set_collides(true);*/

	rectangles.push_back(rec0);
	rectangles.push_back(rec1);
	rectangles.push_back(rec2);

	while (false == window.shouldClose())
	{
		int left = window.getKeyState(mikroplot::KeyCodes::KEY_LEFT);
		int right = window.getKeyState(mikroplot::KeyCodes::KEY_RIGHT);
		int up = window.getKeyState(mikroplot::KeyCodes::KEY_UP);
		int down = window.getKeyState(mikroplot::KeyCodes::KEY_DOWN);

		int ccw = window.getKeyState(mikroplot::KeyCodes::KEY_R);
		int cw = window.getKeyState(mikroplot::KeyCodes::KEY_T);

		float dx = right - left;
		float dy = up - down;

		float d_rot = ccw - cw;

		float deltaTime = timer.getDeltaTime();

		rectangles[0].move(glm::vec2(dx * movement_speed * deltaTime, dy * movement_speed * deltaTime));
		rectangles[0].rotate(d_rot * rotation_speed * deltaTime);

		printf("%f\n", rectangles[0].get_angle());

		window.setScreen(-10, 10, -10, 10);
		window.drawAxis();

		resetCollisions(rectangles);

		updateRectangles(rectangles,deltaTime);

		renderRectangles(rectangles,window);
		//updateRectangles(rectangles,deltaTime);

		window.update();
	}

	return 0;
}

/*
Palautustiedostot: submissions/t4/test_sat.cpp, submissions/t4/sat.h

Googlaa tekniikka "Separated axis theorem" ja toteuta kahden suorakaiteen
törmäystarkistus tiedostoon sat.h (käytä koodaamiasi lineaarialgebran funktioita
tässä apuna).

Käytä hyödyksi vaikka artikkelia:
https://research.ncl.ac.uk/game/mastersdegree/gametechnologies/previousinformation/physics4collisiondetection/2017%20Tutorial%204%20-%20Collision%20Detection.pdf
tai ChatGPT:tä.
Ohjelmoi testisovellus submissions/t4/test_sat.cpp, jolla voi testata törmäysten
toimintaa. Käyttäjän pitää voida liikuttaa ja rotatoida suorakaiteita.
Testisovellus pitää koodata käyttäen MikRoPlot-kirjastoa.

Lisää törmäystarkistusalgoritmiin törmäyspisteen pinnan normaalivektorin laskeminen

Pisteytys: 4 p täysin toimiva SAT. Normaalin laskeminen +1 p = yht 5 p
*/