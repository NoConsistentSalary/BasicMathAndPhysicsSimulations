#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include <mikroplot/window.h>

namespace harkka
{

	//particle?

	//base shapes/shape makes

	//ConvexObj

	//render object -> engineen
	//update object -> engineen

	typedef std::tuple<bool, glm::vec2, glm::vec2> ContactManifold;

	struct Rect
	{
		glm::vec2 position = { 0.0f, 0.0f };
		glm::vec2 halfsize = { 1.0f, 1.0f };

		float angle = 0.0f;
		bool collides = false;

		glm::vec2 velocity = { 0.0f, 0.0f };
		float mass = 1.0f;
		float angularVelocity = 0.0f;

		bool grabbed = false;
	};

	//Euler-integraattori

	//SAT

	glm::mat4 getModelMatrix(Rect R)
	{
		glm::mat4 matRot = glm::rotate(glm::mat4(1.0f), R.angle, glm::vec3(0, 0, 1));
		glm::mat4 matTrans = glm::translate(glm::mat4(1.0f), glm::vec3(R.position.x, R.position.y, 0.0f));
		glm::mat4 matModel = matTrans * matRot;//vaara jarjestys kertolaskussa johtaa origon ympari pyorimiseen
		return matModel;
	}

	std::vector< glm::vec2 > getVertices(Rect R)
	{
		std::vector<glm::vec2> vertices =
		{
			glm::vec2(R.halfsize.x, R.halfsize.y),
			glm::vec2(-R.halfsize.x, R.halfsize.y),
			glm::vec2(-R.halfsize.x, -R.halfsize.y),
			glm::vec2(R.halfsize.x, -R.halfsize.y),
			glm::vec2(R.halfsize.x, R.halfsize.y),//is Extra?
		};

		glm::mat4 model = getModelMatrix(R);
		for (glm::vec2& p : vertices)
		{
			//
			glm::vec4 newP = model * glm::vec4(p.x, p.y, 0, 1);//w paikalle pitaa tulla 1
			p.x = newP.x;
			p.y = newP.y;
		}

		return vertices;
	}

	//////////////////////////////////////////////////////////////

	std::vector<glm::vec2> verticesToGLM(std::vector<mikroplot::vec2> vec)
	{
		std::vector<glm::vec2> result;

		for (mikroplot::vec2 v : vec)
		{
			result.push_back(glm::vec2(v.x, v.y));
		}

		return result;
	}

	std::vector<mikroplot::vec2> verticesToMiktoplot(std::vector<glm::vec2> vec)
	{
		std::vector<mikroplot::vec2> result;

		for (glm::vec2 v : vec)
		{
			result.push_back(mikroplot::vec2(v.x, v.y));
		}

		return result;
	}

	//////////////////////////////////////////////////////////////

	std::vector<glm::vec2> calculateEdgeNormals(Rect R)
	{
		std::vector<glm::vec2> normals;

		// Saa kulmat, jotka ovat laskettu oikein
		std::vector<glm::vec2> vertices = getVertices(R);

		for (size_t i = 0; i < vertices.size() - 1; ++i) {
			glm::vec2 edge = vertices[i + 1] - vertices[i];
			glm::vec2 normal = glm::normalize(glm::vec2(-edge.y, edge.x)); // Perpendicular
			normals.push_back(normal);
		}

		return normals;
	}

	glm::vec2 calculateCollisionNormal(const harkka::Rect& rect1, const harkka::Rect& rect2)
	{
		glm::vec2 center1 = rect1.position;
		glm::vec2 center2 = rect2.position;

		glm::vec2 diff = center2 - center1;

		float overlapX = (rect1.halfsize.x + rect2.halfsize.x) - std::abs(diff.x);
		float overlapY = (rect1.halfsize.y + rect2.halfsize.y) - std::abs(diff.y);

		glm::vec2 collisionNormal;

		if (overlapX < overlapY) {
			// Reduce overlap along x-axis
			if (diff.x < 0) {
				collisionNormal = glm::vec2(-1, 0); // Left
			}
			else {
				collisionNormal = glm::vec2(1, 0);  // Right
			}
		}
		else {
			// Reduce overlap along y-axis
			if (diff.y < 0) {
				collisionNormal = glm::vec2(0, -1); // Down
			}
			else {
				collisionNormal = glm::vec2(0, 1);  // Up
			}
		}

		return collisionNormal;
	}

	std::pair<float, float> project(const glm::vec2& axis, Rect R)
	{
		std::vector< glm::vec2 > vertices = getVertices(R);

		float min = std::numeric_limits<float>::max();
		float max = std::numeric_limits<float>::lowest();

		for (const glm::vec2& vertex : vertices) {
			float projection = glm::dot(vertex, axis);
			min = std::min(min, projection);
			max = std::max(max, projection);
		}

		return { min, max };
	}

}