#pragma once
#include "math.h"
#include <glm/glm.hpp>
#include <vector>
#include <mikroplot/window.h>
#include <glm/gtc/matrix_transform.hpp>

namespace sat
{

	class SAT_Rect
	{
	public:

		SAT_Rect(glm::vec2 pos, glm::vec2 hs,float ang):
			position(pos),halfsize(hs),angle(ang)
		{
			;
		}

		~SAT_Rect()
		{
			;
		}

		glm::mat4 getModelMatrix() const
		{
			auto matRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1));
			auto matTrans = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));
			auto matModel = matTrans * matRot;//vaara jarjestys kertolaskussa johtaa origon ympari pyorimiseen
			return matModel;
		}


		std::vector< mikroplot::vec2 > getVertices() const
		{
			std::vector<glm::vec2> vertices =
			{
				glm::vec2(halfsize.x, halfsize.y),
				glm::vec2(-halfsize.x, halfsize.y),
				glm::vec2(-halfsize.x, -halfsize.y),
				glm::vec2(halfsize.x, -halfsize.y),
				glm::vec2(halfsize.x, halfsize.y),
			};

			auto model = getModelMatrix();
			for (auto& p : vertices)
			{
				//
				auto newP = model * glm::vec4(p.x, p.y, 0, 1);//w paikalle pitaa tulla 1
				p.x = newP.x;
				p.y = newP.y;
			}

			std::vector<mikroplot::vec2> verts;
			for (const auto& v : vertices)
			{
				verts.push_back({ v.x,v.y });
			}

			return verts;
		}


		std::vector<glm::vec2> calculateEdgeNormals()
		{
			std::vector<glm::vec2> normals;

			// Saa kulmat, jotka ovat laskettu oikein
			std::vector<mikroplot::vec2> mvertices = getVertices();
			std::vector<glm::vec2> vertices = verticesGLM(mvertices);

			for (size_t i = 0; i < vertices.size() - 1; ++i) {
				glm::vec2 edge = vertices[i + 1] - vertices[i];
				glm::vec2 normal = glm::normalize(glm::vec2(-edge.y, edge.x)); // Perpendicular
				normals.push_back(normal);
			}

			return normals;
		}

		std::pair<float, float> project(const glm::vec2& axis)
		{
			std::vector< glm::vec2 > vertices = verticesGLM(getVertices());

			float min = std::numeric_limits<float>::max();
			float max = std::numeric_limits<float>::lowest();

			for (const glm::vec2& vertex : vertices) {
				float projection = glm::dot(vertex, axis);
				min = std::min(min, projection);
				max = std::max(max, projection);
			}
			
			return { min, max };
		}

		void move(glm::vec2 p){ position += p; }
		void rotate(float f) { angle += f; }

		void set_collides(bool c) { collides = c; }
		void set_position(glm::vec2 p) { position = p; }
		void set_angle(float a) { angle = a; }

		bool get_collides() { return collides; }
		float get_angle() { return angle; }

	private:
		std::vector<glm::vec2> verticesGLM(std::vector<mikroplot::vec2> vec)
		{
			std::vector<glm::vec2> result;

			for (mikroplot::vec2 v : vec)
			{
				result.push_back(glm::vec2(v.x, v.y));
			}

			return result;
		}

		//Rectangle rect;
		glm::vec2 position = { 0.0f, 0.0f };
		glm::vec2 halfsize = { 1.0f, 1.0f };
		float angle = 0.0f;
		bool collides = false;
	};

}
