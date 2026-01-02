#include <iostream>

#include <glm/glm.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "math.h"
#include "mikroplot/window.h"


#include "harkka.h"

////////////////////////////////////////////////////////////////////////////////


class PhysicsEngine
{
public:
	PhysicsEngine(glm::vec2 bounds):system_boundaries(bounds)
	{
		;
	}

	~PhysicsEngine()
	{
		;
	}

	void render(mikroplot::Window &window) const
	{
		for (harkka::Rect rect : m_rectangles)
		{
			std::vector<glm::vec2> vert = harkka::getVertices(rect);

			if(rect.collides)
				window.drawLines(harkka::verticesToMiktoplot(vert),8);
			else
				window.drawLines(harkka::verticesToMiktoplot(vert),9);
		}
	}

	void update(float deltaTime)
	{
		resetCollisions();
		applyPhysics(deltaTime);

		checkOutOfBounds();
		
		//USE DELTATIME FOR ALL

		for (size_t i = 0; i < m_rectangles.size(); i++)
		{

			for (size_t j = 0; j < m_rectangles.size(); j++)
			{
				if (i != j)
				{
					glm::vec2 normal = glm::vec2(0);
					float depth = 0.0f;
					if (check_SAT_collisions(
						m_rectangles[i], m_rectangles[j],
						normal, depth
					))
					{
						m_rectangles[i].position += normal * depth;

						m_rectangles[i].velocity = reflect(m_rectangles[i].velocity, normal);
						m_rectangles[j].velocity = reflect(m_rectangles[j].velocity, normal);

						glm::vec2 relativeVelocity = m_rectangles[j].velocity - m_rectangles[i].velocity;
						glm::vec2 contactPoint = (m_rectangles[i].position + m_rectangles[j].position) * 0.5f;

						glm::vec2 r1 = contactPoint - m_rectangles[i].position;
						glm::vec2 r2 = contactPoint - m_rectangles[j].position;

						float angularImpulse1 = glm::dot(relativeVelocity, normal) * glm::length(r1);
						float angularImpulse2 = glm::dot(relativeVelocity, normal) * glm::length(r2);

						m_rectangles[i].angularVelocity += angularImpulse1;
						m_rectangles[j].angularVelocity -= angularImpulse2;
					}
				}

				
			}
		}
	}

	void addRectangle(glm::vec2 pos, glm::vec2 halfsiz, float ang)
	{
		harkka::Rect rectangle({ pos,halfsiz,ang,false});
		rectangle.velocity = glm::vec2({0.0f,1.0f});
		rectangle.angularVelocity = 0.0f;
		m_rectangles.push_back(rectangle);
	}

	void checkMouseGrab(glm::vec2 mpos,float mw)
	{
		for (harkka::Rect& rect : m_rectangles)
		{
			if (isPointInRectangle(mpos, rect))
			{
				rect.position = mpos;
				rotate(rect, mw);
				rect.velocity = glm::vec2(0);
				rect.angularVelocity = 0.0f;

				rect.grabbed = true;
			}
		}
	}

	void move(int i, glm::vec2 mov)
	{
		m_rectangles[i].position += mov;
	}
	
	void rotate(harkka::Rect& r, float rot)
	{
		r.angle += rot*0.01;
	}

	int getRectCount()
	{
		return m_rectangles.size();
	}

	void deleteGrabbed()
	{
		for (size_t i = 0; i < m_rectangles.size(); i++)
		{
			if (m_rectangles[i].grabbed)
			{
				m_rectangles.erase(m_rectangles.begin() + i);
			}
		}
	}

private:
	//
	std::vector<harkka::Rect> m_rectangles;

	glm::vec2 system_boundaries;

	//GRAVITY, ROTATION SPEED, ...

	float Gravity = 0.0f;
	float RotationSpeed = 2.0f;

	void change_x_dir(harkka::Rect& rect) { rect.velocity.x *= -1.0f; }
	void change_y_dir(harkka::Rect& rect) { rect.velocity.y *= -1.0f; }


	bool check_SAT_collisions(harkka::Rect &rect1, harkka::Rect &rect2, glm::vec2& normal, float& depth)
	{
		normal = glm::vec2(0);
		depth = std::numeric_limits<float>::max();

		std::vector<glm::vec2> axes1 = calculateEdgeNormals(rect1);
		std::vector<glm::vec2> axes2 = calculateEdgeNormals(rect2);

		for (const auto& axes : axes1)
		{
			auto [min1, max1] = project(axes, rect1);
			auto [min2, max2] = project(axes, rect2);

			if (max1 < min2 || max2 < min1)
			{
				return false;
			}

			float axisDepth = std::min(
				(max2 - min1),
				(max1 - min2)
			);
			if (axisDepth < depth)
			{
				depth = axisDepth;
				normal = (min1 < min2) ? -axes : axes;
			}
		}

		for (const auto& axes : axes2)
		{
			auto [min1, max1] = project(axes, rect1);
			auto [min2, max2] = project(axes, rect2);

			if (max1 < min2 || max2 < min1)
			{
				return false;
			}

			float axisDepth = std::min(
				(max2 - min1),
				(max1 - min2)
			);
			if (axisDepth < depth)
			{
				depth = axisDepth;
				normal = (min1 < min2) ? -axes : axes;
			}
		}

		rect1.collides = true;
		rect2.collides = true;

		return true;
	}

	void checkOutOfBounds()
	{
		for (harkka::Rect& r : m_rectangles)
		{
			std::vector< glm::vec2 > vert = harkka::getVertices(r);
			
			for (size_t i = 0; i < 4; i++)
			{

				if(vert[i].x < -system_boundaries.x || vert[i].x > system_boundaries.x)
				{

					float dif = std::abs(std::abs(vert[i].x) - std::abs(system_boundaries.x));

					if (vert[i].x < -system_boundaries.x)
					{
						r.position.x += dif;
					}

					if (vert[i].x > system_boundaries.x)
					{
						r.position.x -= dif;
					}

					change_x_dir(r);
				}
				if (vert[i].y < -system_boundaries.y || vert[i].y > system_boundaries.y)
				{

					float dif = std::abs(std::abs(vert[i].y) - std::abs(system_boundaries.y));

					if (vert[i].y < -system_boundaries.y)
					{
						r.position.y += dif;
					}

					if (vert[i].y > system_boundaries.y)
					{
						r.position.y -= dif;
					}

					change_y_dir(r);
				}

			}
		}
	}

	void resetCollisions()
	{
		for (harkka::Rect &rect : m_rectangles)
		{
			rect.collides = false;
		}
	}

	bool isPointInRectangle(glm::vec2 point,harkka::Rect& r)
	{
		bool inside = false;

		std::vector< glm::vec2 >vertices = getVertices(r);
		size_t count = vertices.size();

		for (size_t i = 0, j = count - 1; i < count; j = i++)
		{
			if (
				((vertices[i].y > point.y) != (vertices[j].y > point.y)) &&
				(point.x < (vertices[j].x - vertices[i].x) * (point.y - vertices[i].y) / 
				(vertices[j].y - vertices[i].y) + vertices[i].x))
			{
				inside = !inside;
			}
		}
		return inside;
	}

	void applyPhysics(float deltaTime)
	{
		for (harkka::Rect& rect : m_rectangles)
		{
			rect.velocity += glm::vec2(0, -9.81f) * deltaTime;
			rect.position += rect.velocity * deltaTime;
			rect.angle += rect.angularVelocity * deltaTime;
			rect.angularVelocity *= 0.99f;
		}
	}

	//METHOD FOR COLLISION RECTIONS FOR OBJECTS
	//METHOD FOR GETTING THE COLLISIONS TO NET GET STUCK
	//CANT ADD RECTANGLES OUTSIDE THE BOUNDARIES
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main()
{
	mikroplot::Window window(800, 800, "Harkkatyo");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& IO = ImGui::GetIO();
	//
	ImGui::StyleColorsClassic();

	ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 150");

	mikroplot::Timer timer;

	PhysicsEngine engine(glm::vec2( {10,10} ));

	window.setClearColor(19);

	float rect_halfsizeX = 0.5f;
	float rect_halfsizeY = 0.5f;
	float rect_angle = 0.0f;

	engine.addRectangle(glm::vec2({ 0.0,0.0 }), glm::vec2({ 1.0,1.0 }), 4.0f);
	/*engine.addRectangle(glm::vec2({ -8.0,-8.0 }), glm::vec2({ 0.5,0.5 }), 1.0f);
	engine.addRectangle(glm::vec2({ 8.0,8.0 }), glm::vec2({ 0.5,0.5 }), 0.3f);*/

	while (false == window.shouldClose())
	{

		int left = window.getKeyState(mikroplot::KeyCodes::KEY_LEFT);
		int right = window.getKeyState(mikroplot::KeyCodes::KEY_RIGHT);
		int up = window.getKeyState(mikroplot::KeyCodes::KEY_UP);
		int down = window.getKeyState(mikroplot::KeyCodes::KEY_DOWN);
		

		float dx = right - left;
		float dy = up - down;

		float deltaTime = timer.getDeltaTime();

		//engine.move(0,glm::vec2(dx * 2.5 * deltaTime, dy * 2.5 * deltaTime));

		

		window.setScreen(-10, 10, -10, 10);
		//window.drawAxis();

		engine.update(deltaTime);
		engine.render(window);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Democontols", 0, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Control demo from here");
		ImGui::Text("Left Click grabs object and can be moved. dont move mouse too fast");
		ImGui::Text("Right click creates new object");
		ImGui::Text("Scrollwheel rotates object");

		ImGui::SliderFloat("Created rectangles halfsize X", &rect_halfsizeX, 0.1f, 5.0f);
		ImGui::SliderFloat("Created rectangles halfsize Y", &rect_halfsizeY, 0.1f, 5.0f);
		ImGui::SliderAngle("Created rectangles inital angle", &rect_angle, 0, 360);
		
		ImGui::Text("Rectangle count: %i", engine.getRectCount());

		ImVec2 mpos = ImGui::GetMousePos();
		ImVec2 windowPos = ImGui::GetWindowPos(); // Get window position
		glm::vec2 relativeMousePos = glm::vec2(mpos.x-400, 400-mpos.y);
		relativeMousePos *= 0.025;
		ImGui::Text("Relative Mouse Position: (%.1f, %.1f)", relativeMousePos.x, relativeMousePos.y);

		
		if (ImGui::IsMouseDown(0)/*ImGui::IsMouseClicked(0)*/)
		{

			float mw = IO.MouseWheel;
			engine.checkMouseGrab(relativeMousePos,mw);
			/*ImGui::GetMouseDragDelta;
			ImGui::CaptureMouseFromApp;
			ImGui::IsMousePosValid;*/
			
		}
		if (ImGui::IsMouseClicked(1))
		{
			printf("MOUSE CLICKED!\n");
			engine.addRectangle(relativeMousePos, glm::vec2({ rect_halfsizeX,rect_halfsizeY }), rect_angle);
		}
		if(ImGui::IsKeyDown(ImGuiKey_Space))
		{
			engine.deleteGrabbed();
		}

		//ImGui::SliderAngle("Kulma", &initial_angle);
		//ImGui::SliderFloat("Initial Speed", &initial_speed, 1.0f, 10.0f);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.update();
	}
}

/*
Palautustiedosto: submissions/practical_work/physics_demo.cpp

  Yksinkertainen 2D-fysiikkamoottori

* 2D-laatikot, (position, rotation) (1 p)															X
	(aka.)

* Euler-integraattori (1 p)																			juu?
	(aka.)

* SAT törmäykset, jotta toimii myös rotetoiduilla laatikoilla (1 p)									X
	(aka.)

* Törmäyksiin reagointi impulsseinm Ei kitkaa, Törmäyksen restituutiokerroin välillä 0-1 (1 p)		jotain?
	(aka. lasketaan törmäykset ja restetuutio = kimmoisuus)

* Demossa useampi laatikko, joihin vaikuttaa gravitaatio. (1 p)										juu
	(aka. yksinkertainen gravitaatio)

* Laatikoita pitää voida lisätä/liikutella. (1 p)													X
	(aka.imgui ja hiiriliikutus)

* Toimii realistisesti ja ei bugaile (1 p)															...
	(aka. ei ole aivan perseestä)

TAI on mahdollista että harjoitustyön tekee jonkinlaisen muun demon, kuin edellä kuvatun SAT
boxi systeemin, mutta siitä on sovittava opettajan kanssa erikseen (vaikkapa sähköpostilla)

Huom! Ei haittaa, jos harjoitustyöhön jää jotakin bugeja tms. Pääasia, että pääsääntöisesti
toimii ongelmitta, jos joskus jotekin bugeja ilmenee esim laatikot tarttuvat toisiinsa tai muuta
jännää, niin se ei haittaa.
*/

/*
-400-400				+400-400

-400+400				+400+400



-10+10

-10-10
*/