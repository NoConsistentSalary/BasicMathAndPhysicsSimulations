#include <stdio.h>
#include <mikroplot/window.h>
#include <glm/glm.hpp>


#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

struct Particle
{
	glm::vec2 position;
	//oletetaan massa = 1kg
	glm::vec2 velocity;
};

void simulate(std::vector<Particle>&bodies, float deltatime)
{
	auto g = glm::vec2(0,-9.81);
	auto wind = glm::vec2(-1.0f, 0);

	for (size_t i = 0; i < bodies.size(); i++)
	{
		/*float p = 1.0f;
		float A = 1.0f;
		float C = 1.0f;
		auto F = 0.5f * p * glm::dot(bodies[i].velocity, bodies[i].velocity) * A * C;*/
		bodies[i].velocity += (g/*+wind*/) * deltatime;

		bodies[i].position += bodies[i].velocity * deltatime;
	}
}

void add_particle(std::vector<Particle>& particles, float angle, float speed)
{
	glm::vec2 position = glm::vec2(0);
	glm::vec2 direction = glm::vec2(0.0f, 0.0f);

	//
	direction.x = cosf(angle);
	direction.y = sinf(angle);


	direction = glm::normalize(direction);

	assert(abs(1.0f - glm::length(direction)) < 0.01f);

	//suuntavektori kulmaksi
	//atan2f(y,f) -> kulma

	glm::vec2 velocity = direction * speed;

	particles.push_back(Particle{ position, velocity });
}

void render_particles(auto& window,const auto& particles)
{
	std::vector<mikroplot::vec2> points;
	for (const auto& p : particles)
	{
		points.push_back({ p.position.x,p.position.y });
	}
	window.drawPoints(points, 11, 6);
}

int main()
{
	mikroplot::Window window(800, 800, "particles");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();
	//ImGui::StyleColorsClassic();

	

	std::vector<Particle> particles/* = {
		Par
	}*/;
	particles.push_back(Particle{ glm::vec2(), glm::vec2() });

	

	ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 150");
	mikroplot::Timer timer;
	float initial_angle = 3.1415f/4.0f;
	float initial_speed = 5.0f;

	while (false == window.shouldClose())
	{
		float deltatime = timer.getDeltaTime();
		simulate(particles,deltatime);

		window.setScreen(-10, 10, -10, 10);
		window.drawAxis();

		render_particles(window,particles);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//draw gui
		ImGui::Begin("partikkeliefekti",0,ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Here is some text");
		if (ImGui::Button("Add particle"))
		{
			printf("BUTTON PRESSED!\n");
			add_particle(particles, initial_angle, initial_speed);
		}


		//sliderit vauhdille ja kulmalle
		ImGui::SliderAngle("Kulma", &initial_angle);
		ImGui::SliderFloat("Initial Speed", &initial_speed, 1.0f, 10.0f);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		window.update();


	}

	printf("%i\n", particles.size());

	return 0;
}