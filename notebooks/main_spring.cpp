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
	glm::vec2 attachPoint;
};
///////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////
void render_particles(auto& window,const auto& particles)
{
	std::vector<mikroplot::vec2> points;
	for (const auto& p : particles)
	{
		points.push_back({ p.position.x,p.position.y });
	}
	window.drawPoints(points, 12, 6);

	std::vector<mikroplot::vec2> lines;
	for (const auto& p : particles)
	{
		lines.push_back({ p.position.x,p.position.y });
		lines.push_back({ p.attachPoint.x,p.attachPoint.y });
	}
	window.drawLines(lines, 11, 2, true);
}
///////////////////////////////////////////////////////////
void add_spring_particle(auto& particles, const glm::vec2& position, const glm::vec2& attachPointeed)
{
	Particle part;
	part.position = position;
	part.attachPoint = attachPointeed;
	part.velocity = glm::vec2(0);
	particles.push_back(part);
}
///////////////////////////////////////////////////////////
void simulate_spring(std::vector<Particle>&bodies, float deltatime)
{
	const auto g = glm::vec2(0,-9.81);
	//auto wind = glm::vec2(-1.0f, 0);
	//F = -k*x, jossa k = jousivakio, x=poikkeama tasapainoasemasta

	const auto k = 10.0f;

	glm::vec2 windForce(-1, 0);

	for (size_t i = 0; i < bodies.size(); i++)
	{
		/*float p = 1.0f;
		float A = 1.0f;
		float C = 1.0f;
		auto F = 0.5f * p * glm::dot(bodies[i].velocity, bodies[i].velocity) * A * C;*/


		
		auto x = bodies[i].position - bodies[i].attachPoint;
		auto springF = -k * x;

		auto totalForce = g + springF + windForce;

		//vakiovaimennus
		bodies[i].velocity *= 0.99f;

		bodies[i].velocity += (totalForce) * deltatime;

		bodies[i].position += bodies[i].velocity * deltatime;
	}
}





int main()
{
	mikroplot::Window window(800, 800, "Spring demo");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	

	std::vector<Particle> particles;
	//particles.push_back(Particle{ glm::vec2(), glm::vec2() });

	//add_particle(particles, 0, 0);

	auto initial_position = glm::vec2(0, 0);
	auto attachPoint = glm::vec2(5, 5);

	add_spring_particle(particles,initial_position,attachPoint);

	

	ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 150");
	mikroplot::Timer timer;
	

	while (false == window.shouldClose())
	{
		float deltatime = timer.getDeltaTime();
		simulate_spring(particles,deltatime);

		window.setScreen(-10, 10, -10, 10);
		window.drawAxis();
		//window.drawCircle({ 0,0 }, 3.0f);
		render_particles(window,particles);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		

		////draw gui
		//ImGui::Begin("partikkeliefekti",0,ImGuiWindowFlags_AlwaysAutoResize);
		//ImGui::Text("Here is some text");
		//if (ImGui::Button("Add particle"))
		//{
		//	printf("BUTTON PRESSED!\n");
		//	add_particle(particles, initial_angle, initial_speed);
		//}


		////sliderit vauhdille ja kulmalle
		//ImGui::SliderAngle("Kulma", &initial_angle);
		//ImGui::SliderFloat("Initial Speed", &initial_speed, 1.0f, 10.0f);

		//ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		window.update();


	}
	return 0;
}