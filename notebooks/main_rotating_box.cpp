#include <stdio.h>
#include <mikroplot/window.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <complex>
#include <glm/gtc/quaternion.hpp>

struct Box
{
	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	glm::vec2 halfSize = glm::vec2(0.5f, 0.5f);
	float angle = 0.0f;

	Box* parent = nullptr;

	glm::mat4 getModelMatrix() const
	{
		auto matRot = glm::rotate(glm::mat4(1.0f),angle, glm::vec3(0,0,1));
		auto matTrans = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));
		auto matModel = matTrans * matRot;//vaara jarjestys kertolaskussa johtaa origon ympari pyorimiseen
		return matModel;
	}

	glm::mat4 getWorlTransform() const
	{
		if (parent)
		{
			return parent->getWorlTransform() * getModelMatrix();
		}
		return getModelMatrix();
	}

	auto getVertices() const
	{
		std::vector<glm::vec2> points;

		points.push_back(glm::vec2(halfSize.x, halfSize.y));//oikYla
		points.push_back(glm::vec2(-halfSize.x, halfSize.y));//vasYla
		points.push_back(glm::vec2(-halfSize.x, -halfSize.y));//
		points.push_back(glm::vec2(halfSize.x, -halfSize.y));//
		points.push_back(glm::vec2(halfSize.x, halfSize.y));
#if 0
		//rotatoi karkipisteet kulman verran
		auto rot = std::complex<float>(std::cos(angle), std::sin(angle));
		for (auto& p : points)
		{
			auto c = std::complex<float>(p.x, p.y);
			c = rot * c * rot;
			p.x = c.real();
			p.y = c.imag();
		}

		//siirrä karkipisteet paikoilleen
		for (auto& p : points)
		{
			p = p + position;
		}
#else
		//
		auto model = getWorlTransform();
		for (auto& p : points)
		{
			//
			auto newP = model * glm::vec4(p.x,p.y,0,1);//w paikalle pitaa tulla 1
			p.x = newP.x;
			p.y = newP.y;
		}
#endif

		std::vector<mikroplot::vec2> verts;
		for (const auto& v : points)
		{
			verts.push_back({v.x,v.y});
		}

		return verts;
	}

	void render(mikroplot::Window& window) const
	{
		auto vertices = getVertices();

		window.drawLines(vertices);
	}
};

int main() {
	Box box;
	box.position.x = 3.0f;
	box.position.y = 1.0f;
	box.halfSize.x = 1.5f;
	box.halfSize.y = 1.0f;

	Box rightFrontTire;
	rightFrontTire.position.x = 1.0f;
	rightFrontTire.position.y = -1.0f;
	rightFrontTire.halfSize.x = 0.4f;
	rightFrontTire.halfSize.y = 0.20f;
	rightFrontTire.parent = &box;

	Box leftFrontTire;
	leftFrontTire.position.x = 1.0f;
	leftFrontTire.position.y = 1.0f;
	leftFrontTire.halfSize.x = 0.4f;
	leftFrontTire.halfSize.y = 0.20f;
	leftFrontTire.parent = &box;

	Box rightBackTire;
	rightBackTire.position.x = -1.0f;
	rightBackTire.position.y = -1.2f;
	rightBackTire.halfSize.x = 0.4f;
	rightBackTire.halfSize.y = 0.35f;
	rightBackTire.parent = &box;

	Box leftBackTire;
	leftBackTire.position.x = -1.0f;
	leftBackTire.position.y = 1.2f;
	leftBackTire.halfSize.x = 0.4f;
	leftBackTire.halfSize.y = 0.35f;
	leftBackTire.parent = &box;

	mikroplot::Window window(800, 800, "Rotating box!");
	mikroplot::Timer timer;
	while (false == window.shouldClose()) {
		float deltaTime = timer.getDeltaTime();
		float w = 2.0f * 3.1415f;
		box.angle += 0.5f * w * deltaTime;

		window.setScreen(-10, 10, -10, 10);
		window.drawAxis();

		//rendaa runko ja renkaat
		box.render(window);
		rightFrontTire.render(window);
		leftFrontTire.render(window);
		rightBackTire.render(window);
		leftBackTire.render(window);
		window.update();
	}
	return 0;
}