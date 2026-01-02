#include <glm/glm.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <mikroplot/window.h>

#include <stdio.h>
#include <iostream>
//#include <chrono>
//#include <cstdlib>
#include <random>

struct Particle
{
	glm::vec2 position;
	glm::vec2 velocity;

	float lifespan;
	float age;

	//Color
};

//*********************************************************************

class ParticleEmitter
{
public:
	ParticleEmitter(
		glm::vec2 &pos, glm::vec2 &dir,			//
		float &ang, float minS, float &maxS,	//angle and min max speeds
		int xboundary,int yboundary,			//stages boundaries
		float &windangle, float& windspeed,		//winds angle and speed
		bool &randspeed,						//random initial speed for particle
		bool &deltionstyle						//deletion style as out of bounds or lifetime
	):
		position(pos),direction(dir),angle(ang),minSpeed(minS),maxSpeed(maxS),
		Xboundary(xboundary),Yboundary(yboundary),
		windAngle(windangle), windSpeed(windspeed),
		randSpeed(randspeed),
		deleteTroughLifetime(deltionstyle)
	{
		//srand(time(0));
	}

	~ParticleEmitter()
	{
		printf("Particls left: %i\n",particles.size());
		particles.clear();
	}

	void add_particle()
	{

		assert(abs(1.0f - glm::length(direction)) < 0.01f);

		//randomize float speed
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distribspeed(minSpeed, maxSpeed);
		std::uniform_int_distribution<> distribamount(10, 30);

		float speed = 0;

		if (randSpeed)
		{
			speed = distribspeed(gen);
		}
		else
		{
			speed = maxSpeed;
		}
		
		int amount = distribamount(gen);

		glm::vec2 velocity = direction * speed;

		particles.push_back(Particle{ position, velocity, 10.0f, 0.0f });
	}

	void update(float deltaTime)
	{
		//update the spray direction according the angle
		direction.x = cosf(angle);
		direction.y = sinf(angle);
		direction = glm::normalize(direction);

		//Set gravity and wind
		glm::vec2 g = glm::vec2(0, -9.80665f);
		glm::vec2 wind = glm::vec2( cosf(windAngle), sinf(windAngle));//glm::vec2(-1.0f, 0);
		wind *= windSpeed;

		//update particles age velocity and position
		for (size_t i = 0; i < particles.size(); i++)
		{
			particles[i].age += deltaTime;

			particles[i].velocity += (g+wind)*deltaTime;

			particles[i].position += particles[i].velocity * deltaTime;
		}

		//delete out of bound or lifetime particles
		if(deleteTroughLifetime)
		{ check_lifetime(); }
		else
		{ check_out_of_bounds(); }
				
	}

	void render(auto& window)
	{
		std::vector<mikroplot::vec2> points;

		for (const auto& p : particles)
		{
			points.push_back({ p.position.x,p.position.y });
		}

		//draw the particles
		window.drawPoints(points, 8, 10.0f);//rendom v�ri kelta/puna asteikolta?

		glm::vec2 wind = glm::vec2(cosf(windAngle), sinf(windAngle));

		//draw the vector for particle emitters direction
		std::vector<mikroplot::vec2> rotdir = { glm_to_mikroplot(position), glm_to_mikroplot(direction) };
		window.drawLines(rotdir,10,3);

		//draw the vector for wind direction
		std::vector<mikroplot::vec2> winddir = { glm_to_mikroplot(position), glm_to_mikroplot(wind) };
		window.drawLines(winddir, 9, 3);
	}

private:

	mikroplot::vec2 glm_to_mikroplot(glm::vec2 v)
	{
		return mikroplot::vec2(v.x,v.y);
	}

	//deletes particles if out of bounds
	void check_out_of_bounds()
	{

		if (particles.size())
		{
			for (size_t i = 0; i < particles.size(); i++)
			{
				if (particles[i].position.y < -Yboundary)
				{
					particles.erase(particles.begin() + i);
					//printf("deleted particle\n");
				}
			}
		}

	}

	//deletes particles if lifetime is over
	void check_lifetime()
	{

		if (particles.size())
		{
			for (size_t i = 0; i < particles.size(); i++)
			{
				if (particles[i].age >= particles[i].lifespan)
				{
					particles.erase(particles.begin() + i);
					//printf("deleted particle\n");
				}
			}
		}

	}

	std::vector<Particle> particles;

	int Xboundary;
	int Yboundary;

	glm::vec2 &position;
	glm::vec2 &direction;

	float &angle;
	float minSpeed;
	float &maxSpeed;

	float &windAngle;
	float& windSpeed;

	bool &randSpeed;
	bool& deleteTroughLifetime;
	//random color

};

//*********************************************************************

int main()
{
	mikroplot::Window window(800,800,"Particle Emitter");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& IO = ImGui::GetIO();

	ImGui::StyleColorsClassic();

	ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 150");

	mikroplot::Timer timer;

	glm::vec2 position = glm::vec2(0);
	glm::vec2 direction = glm::vec2(0.0f, 0.0f);

	float initial_angle = 3.1415f / 4.0f;
	float initial_speed = 5.0f;

	float wind_angle = 0.0f;
	float wind_speed = 0.0f;

	int spawn_per_sec = 10;
	//float particles_lifespan = 10.0f;

	bool rand_spawnrate = true;		//particles spawnrate per second
				//bool rand_angle = false;			//
	bool rand_speed = true;			//particles random speed
	bool deletion_style = true;		//

	int refreshrate = 1;			//assumes that runs 60 frames per second

	//particle emitter initialization
	ParticleEmitter emitter(
		position,direction,
		initial_angle,
		1, initial_speed,
		10,10,
		wind_angle, wind_speed,
		rand_speed,
		deletion_style
	);

	while (false == window.shouldClose())
	{
		float deltatime = timer.getDeltaTime();

		//update emitter aka simulate particles
		emitter.update(deltatime);

		window.setScreen(-10, 10, -10, 10);
		window.drawAxis();

		//particle rendering
		emitter.render(window);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		//draw gui
		ImGui::Begin("partikkeliefekti", 0, ImGuiWindowFlags_AlwaysAutoResize);

		//sliders
		ImGui::Text("Sliders");
		ImGui::SliderAngle("Particle emitter angle", &initial_angle,0,360);
		ImGui::SliderAngle("Wind angle", &wind_angle, 0, 360);
		ImGui::SliderFloat("Initial particle speed", &initial_speed, 1.0f, 10.0f);
		ImGui::SliderFloat("Wind speed", &wind_speed, -5.0f, 5.0f);
		ImGui::SliderInt("Particle spawnrate per sec", &spawn_per_sec,1,30);
		

		//checkboxes
		ImGui::Text("Checkboxes");
		ImGui::Checkbox("Random particle initial speed", &rand_speed);
		ImGui::Checkbox("Spawn particles automatically", &rand_spawnrate);
		ImGui::Checkbox("Delete when lifetime is over(true)/when out of bounds(false)", &deletion_style);


		if(false == rand_spawnrate)
		{
			if (ImGui::Button("Add particle"))
			{
				printf("BUTTON PRESSED!\n");
				emitter.add_particle();
			}
		}
		// if particles are spawned automatically, than calculated approximate spawn rate per second
		// its assumed that the game runs 60 fps
		else
		{
			if (refreshrate >= (60 / spawn_per_sec) )
			{
				emitter.add_particle();
				refreshrate = 0;
			}

			refreshrate++;

		}

		//set lifetme (in seconds)
		//set rand direction to particles as well?
		//rand x an y speed?

		//print data at rate and clean it up

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.update();

		//window.drawSprite
		//window.playSound();
	}

	return 0;
}

/*	Palautustiedosto: submissions/t5/particle_demo.cpp

 - Tee yksinkertainen partikkeliefekti demo (kipin�suihku).

 - Partikkeli emitter -luokka, jolla seuraavat attribuutit (1,5 p):										X
	 - position (vec2)
	 - direction (vec2)
	 - angle (esim 0.1 rad, kartion kulma)
	 - minSpeed (float m/s)
	 - maxSpeed (float m/s).

 - Suuunnittele ja toteuta ParticleEmitterille metodit, jotka n�et tarpeelliseksi (1,5 p).				X

 - Simulaation ulkoiset voimat (1 p):																	X
	 - Gravitaatio
	 - Tuuli (vec2)

 - Tee partikkelidemo, joka spawnaa 10-30 partikkeli� sekunnissa. Partikkeleilla elinik� 10 sekuntia.
   N�it� pit�isi voida s��t�� k�ytt�liittym�st� (1 p).													X
*/

/*
MIN:

tuulivoima

s��t�minen:
	min/max speed, kartion kulma
	elini�lle,spawnausm��r�lle ja randomisointi t�pp�, 
	gravitaatiolle,tuulelle,

*/


/*			More ideas:
 - pystyy lis��m��n emitterej�
 - 
 - USE ALL CLASS VARIABLES!!!
 - automatic particle emition
 - random particle directions (angle and speed)
 - random particle firing rate (other effects like tiny explosions)
 - random particle color
 - multiple particles per seconds
 - particle lifespand 10 seconds
 - particles shrink as they die (maby also chainge color)? 
 - PLAYS SOUND (mikroplot function offerend)

 - Popcorn effect?
 https://www.freepik.com/premium-vector/cartoon-popcorn-shapes-film-tv-snacks-popping-corn-cinema-fun-food-various-shapes-vector-isolated-set_29461544.htm
 ...
*/