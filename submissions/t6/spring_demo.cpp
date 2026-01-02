#include <stdio.h>
#include <mikroplot/window.h>
#include <glm/glm.hpp>


#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


struct Particle
{
	glm::vec2 position;
	glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
};

struct Spring
{
	Particle* particle;
	std::vector<glm::vec2> attachPoints;
	std::vector < Particle* > parents;
};



class SpringSystem
{
public:
	SpringSystem(std::vector<Spring> &s):
		springs(s)
	{}

	~SpringSystem()
	{
		for (Spring& s : springs)
		{
			if (s.parents.size())
			{
				for (Particle* p : s.parents)
				{
					delete p;
					p = 0;
				}
				s.parents.clear();
			}
			delete s.particle;
			s.particle = 0;
		}

		springs.clear();
	}

	void add_whole_cloth(const std::vector<Spring> &cloth)
	{
		springs = cloth;
	}

	void add_spring_particle(Spring s)
	{
		springs.push_back(s);
	}

	void update(float deltaTime)
	{
		const glm::vec2 g = glm::vec2(0, -9.81);

		const float k = 10.0f;

		for (size_t i = 0; i < springs.size(); i++)
		{

			for (glm::vec2 a : springs[i].attachPoints)
			{
				glm::vec2 x = springs[i].particle->position - a;
				glm::vec2 springF = -k * x;

				glm::vec2 totalForce = g + springF + windForce;

				springs[i].particle->velocity *= 0.99f;

				springs[i].particle->velocity += (totalForce)*deltaTime;

				springs[i].particle->position += springs[i].particle->velocity * deltaTime;
			}


		}
	}

	void render(auto& window)
	{
		renderLines(window);
		renderSprings(window);
	}

	void setWindforce(glm::vec2 v) { windForce = v; }

private:
	//-----------------------------------------------

	std::vector<Spring> &springs;//many??
	glm::vec2 windForce = glm::vec2(0, 0);

	void renderSprings(auto& window)
	{
		std::vector<mikroplot::vec2> points;
		for (const auto& s : springs)
		{
			points.push_back({ s.particle->position.x,s.particle->position.y });
		}
		window.drawPoints(points, 20, 6);
	}

	void renderLines(auto& window)
	{
		std::vector<std::vector<mikroplot::vec2>> lines;

		for (const auto& s : springs)
		{

			if (s.attachPoints.size())
			{
				for (const auto& a : s.attachPoints)
				{
					std::vector<mikroplot::vec2> springpart;
					springpart.push_back({ a.x, a.y });
					springpart.push_back({ s.particle->position.x, s.particle->position.y });
					lines.push_back(springpart);
				}
			}
			if (s.parents.size())
			{
				for (const auto& p : s.parents)
				{
					std::vector<mikroplot::vec2> springpart;
					springpart.push_back({ p->position.x, p->position.y });
					springpart.push_back({ s.particle->position.x, s.particle->position.y });
					lines.push_back(springpart);
				}
			}

			//lines.push_back(springpart);
		}

		for (const auto i : lines)
		{
			window.drawLines(i, 7, 2, true);
		}
	}

};

//*********************************************************************



int main()
{

	std::vector<Particle> particles =
	{
		//			Position		Velocity		Attachpoint
		Particle(glm::vec2(0,0)),

		Particle(glm::vec2(0,1)),
		Particle(glm::vec2(0,2)),

		Particle(glm::vec2(1,0)),
		Particle(glm::vec2(1,1)),

		Particle(glm::vec2(2,0)),
		Particle(glm::vec2(2,1)),

		Particle(glm::vec2(3,0)),
		Particle(glm::vec2(3,1)),

		Particle(glm::vec2(4,0)),
		Particle(glm::vec2(4,1)),
	};

	std::vector<Spring> springs =
	{
		//			Position	Attachpoint
		Spring(&particles[0], {glm::vec2(5,10)}),

		Spring(&particles[1], {/*glm::vec2(4,5)*/}, {&particles[0]/*,&particles[3]}*/}),
		//Spring(particles[2], {glm::vec2(4,9)}),

		Spring(&particles[3], {/*glm::vec2(3,5)*/}, {&particles[1]/*,&particles[3]}*/}),
		//Spring(particles[4], {glm::vec2(3,9)}),

		Spring(&particles[5], {glm::vec2(2,5)}),
	};

	mikroplot::Window window(800, 800, "Spring");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& IO = ImGui::GetIO();

	ImGui::StyleColorsClassic();

	ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 150");

	mikroplot::Timer timer;

	SpringSystem system(springs);

	while (false == window.shouldClose())
	{
		int space = window.getKeyState(mikroplot::KeyCodes::KEY_SPACE);

		system.setWindforce(glm::vec2(space, 0));

		float deltatime = timer.getDeltaTime();

		system.update(deltatime);
		//spring0.update(deltatime);

		window.setScreen(-10, 10, -10, 10);
		window.drawAxis();

		system.render(window);
		//spring0.render(window);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.update();
	}

	return 0;
}

/*	Palautustiedosto: submissions/t6/spring_demo.cpp

 - Ns. hooken laki: F = -kx, miss� k = jousivakio ja x poikkama tasapainoasemasta

 - Tee demo, jossa 10 pistem�ist� partikkelia roikkuu jousen varassa. (Jousen yl�kiinnityspiste esim. kohdassa 5,10)

 - Gravitaatio (F=mg) + jousivoima (F=-kx) + vakiovaimennus (joka frame vaikkapa 1% pienempi nopeus)

 - Kullakin partikkelilla pit�� olla oma jousivakio ja massa.

 - S��d� demo toimimaan niin, ett� partikkeli pomppii jousen varassa (2 p).				//juu?

 - Kokeile tehd� my�s jonkinlainen jousiketju/vaatefysiikka, jossa on kytkettyn� useampi partikkeli
   kiinni toisiinsa jousivoimalla (+ 1p).
*/

/*			More ideas:
 - are we creating a single spring class?
*/