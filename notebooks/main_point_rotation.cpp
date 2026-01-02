#include <stdio.h>
#include <mikroplot/window.h>
#include <glm/glm.hpp>
#include <complex>
#include <glm/gtc/quaternion.hpp>

struct RotatingPoint2D
{
	glm::vec2 r;//kehapisteen pisteenpaikka origon suhteen
	float w; //kulmanopeus radiaaneina/sec
};

struct RotatingPoint3D
{
	glm::vec3 r;//kehapisteen pisteenpaikka origon suhteen
	glm::vec3 w; //kulmanopeus radiaaneina/sec
};

void drawPoint(auto& window, const auto& body)
{
	std::vector<mikroplot::vec2> line;
	line.push_back({ 0, 0 });
	line.push_back({ body.r.x, body.r.y });

	window.drawLines(line, 13);
	line.erase(line.begin(),line.begin()+1);//poista eka elementti
	window.drawPoints(line, 12,8);
}

glm::vec2 rotStep(glm::vec2 x0, float deltaTime, float w)
{
	auto r = std::complex(x0.x, x0.y);
	float dw = 0.5f * w * deltaTime;
	auto c = std::complex<float>(std::cos(dw), std::sin(dw));
	auto x1 = c * r * c;

	return glm::vec2(x1.real(), x1.imag());
}

glm::vec3 rotStep(glm::vec3 x0, float deltaTime, glm::vec3 w)
{
	auto r = x0;
	float agle = 0.5f * glm::length(w) * deltaTime;
	glm::quat q = glm::angleAxis(agle, glm::normalize(w));
	auto x1 = q * r * glm::conjugate(q);

	return glm::vec3(x1.x, x1.y, x1.z);
}

int main() {
#if 0
	RotatingPoint2D point;
	point.r.x = 3.0f;
	point.r.y = 0.0f;
	point.w = 2.0f * 3.1415f;
#else
	RotatingPoint3D point;
	point.r.x = 3.0f;
	point.r.y = 0.0f;
	point.r.z = 0.0f;
	point.w = glm::vec3(0.0f,0.1f,1.0f);
#endif

	mikroplot::Window window(800, 800, "Hello window!");
	mikroplot::Timer timer;

	while (false == window.shouldClose()) {
		window.setScreen(-10, 10, -10, 10);
		window.drawAxis();
		float deltaTime = timer.getDeltaTime();
#if 0
		//reaali = 0 imag = 1
		std::complex<float> i = {0,1};

		auto result = i * i * i * i;
		point.r.x = result.real();
		point.r.y = result.imag();
		
#endif

		point.r = rotStep(point.r, deltaTime, point.w);

		drawPoint(window, point);
		//window.drawCircle({ 0,0 }, 3.0f);
		window.update();
	}
	return 0;
}