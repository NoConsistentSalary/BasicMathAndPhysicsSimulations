#pragma once
#include <glm/glm.hpp>

namespace cardemo
{

	static inline mikroplot::vec2 glm_to_mikroplot(glm::vec2 v)
	{ return mikroplot::vec2( v.x,v.y ); }

	static inline glm::vec2 mikroplot_to_glm(mikroplot::vec2 v)
	{ return glm::vec2({ v.x,v.y }); }

	std::vector<glm::vec2> convertVertices(std::vector<mikroplot::vec2> verts)
	{
		std::vector<glm::vec2> vertices;

		for (mikroplot::vec2 v : verts)
		{
			vertices.push_back(mikroplot_to_glm(v));
		}

		return vertices;
	}

	float degreesToRadians(float degrees)
	{ return degrees * (3.1415f / 180.0f); }

	float radiansToDegrees(float radians)
	{ return radians * (180.0f / 3.1415f); }

	//expects to get radians
	glm::vec2 rotatePoint(float angle, const glm::vec2& point)
	{
		auto matRot = glm::rotate(glm::mat4(1.0), angle, glm::vec3(0, 0, 1));
		auto pointRotated = matRot * glm::vec4(point.x, point.y, 0.0f, 1.0f);
		return glm::vec2(pointRotated.x, pointRotated.y);
	}

	glm::vec2 reflect(const glm::vec2& r, const glm::vec2& N)
	{
		return r - 2.0f * dot(r, N) * N;
	}

	class GameObject
	{
	public:
		GameObject():
			position({ 0,0 }), scale({ 1,1 }), rotation(0.0f)
		{
			;
		}

		GameObject(glm::vec2 pos, glm::vec2 sca, float rot) :
			position(pos), scale(sca), rotation(rot)
		{
			;
		}

		virtual ~GameObject()
		{
			;
		}


		glm::vec2 get_position(){ return position; }
		glm::vec2 get_scale() { return scale; }
		float get_rotation() { return rotation; }

		void set_position(glm::vec2 p) { position = p; }
		void set_scale(glm::vec2 s) { scale = s; }
		void set_rotation(float r) { rotation = r; }

	protected:
		glm::vec2 position;
		glm::vec2 scale;
		float rotation;

		void move(glm::vec2 m)
		{ position += m; }

		void rotate(float r)
		{ rotation += r; }

	};

	/*class Rectangle
	{
		glm::vec2 halfsize = { 0.2f, 0.1f };
	};*/

}
