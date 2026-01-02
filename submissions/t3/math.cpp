#include "math.h"

#include <stdexcept>

namespace math
{
	vec2 add(const vec2& lhs, const vec2& rhs)
	{
		vec2 result;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			result[i] = lhs[i] + rhs[i];
		}

		return result;
	}

	vec2 sub(const vec2& lhs, const vec2& rhs)
	{
		vec2 result;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			result[i] = lhs[i] - rhs[i];
		}

		return result;
	}

	vec2 mul(float lhs, const vec2& rhs)
	{
		vec2 result;

		for (size_t i = 0; i < rhs.size(); i++)
		{
			result[i] = rhs[i] * lhs;
		}

		return result;
	}

	vec2 mul(const vec2& lhs, float rhs)
	{
		vec2 result;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			result[i] = lhs[i] * rhs;
		}

		return result;
	}

	vec2 div(const vec2& lhs, float rhs)
	{
		vec2 result;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			result[i] = lhs[i] / rhs;
		}

		return result;
	}

	float dot(const vec2& lhs, const vec2& rhs)
	{
		float result = 0;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			result += lhs[i] * rhs[i];
		}

		return result;
	}

	float cross(const vec2& lhs, const vec2& rhs)
	{
		return (lhs[0] * rhs[1] - rhs[0] * lhs[1]);
	}

	float length(const vec2& vec)
	{
		return sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]));
	}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

	vec3 add(const vec3& lhs, const vec3& rhs)
	{
		vec3 result;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			result[i] = lhs[i] + rhs[i];
		}

		return result;
	}

	vec3 sub(const vec3& lhs, const vec3& rhs)
	{
		vec3 result;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			result[i] = lhs[i] - rhs[i];
		}

		return result;
	}

	vec3 mul(float lhs, const vec3& rhs)
	{
		vec3 result;

		for (size_t i = 0; i < rhs.size(); i++)
		{
			result[i] = rhs[i] * lhs;
		}

		return result;
	}

	vec3 mul(const vec3& lhs, float rhs)
	{
		vec3 result;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			result[i] = lhs[i] * rhs;
		}

		return result;
	}

	vec3 div(const vec3& lhs, float rhs)
	{
		vec3 result;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			result[i] = lhs[i] / rhs;
		}

		return result;
	}

	float dot(const vec3& lhs, const vec3& rhs)
	{
		float result = 0;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			result += lhs[i] * rhs[i];
		}

		return result;
	}

	vec3 cross(const vec3& lhs, const vec3& rhs)
	{
		//return (lhs[0] * rhs[1] - rhs[0] * lhs[1]);
		//			  i  j  k
		//lhs ->	| a, b, c |
		//rhs ->	| a, b, c |

		//voisi tehda myos pilkkomalla ja kayttamalla cross floattia
		float i = +(lhs[1] * rhs[2] - rhs[1] * lhs[2]);
		float j = -(lhs[0] * rhs[2] - rhs[0] * lhs[2]);
		float k = +(lhs[0] * rhs[1] - rhs[0] * lhs[1]);

		vec3 result({ i, j, k });

		return result;
	}

	float length(const vec3& vec)
	{
		return sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2]));
	}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

	vec4 add(const vec4& lhs, const vec4& rhs)
	{
		vec4 result;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			result[i] = lhs[i] + rhs[i];
		}

		return result;
	}

	vec4 sub(const vec4& lhs, const vec4& rhs)
	{
		vec4 result;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			result[i] = lhs[i] - rhs[i];
		}

		return result;
	}

	vec4 mul(float lhs, const vec4& rhs)
	{
		vec4 result;

		for (size_t i = 0; i < rhs.size(); i++)
		{
			result[i] = rhs[i] * lhs;
		}

		return result;
	}

	vec4 mul(const vec4& lhs, float rhs)
	{
		vec4 result;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			result[i] = lhs[i] * rhs;
		}

		return result;
	}

	vec4 div(const vec4& lhs, float rhs)
	{
		vec4 result;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			result[i] = lhs[i] / rhs;
		}

		return result;
	}

	float dot(const vec4& lhs, const vec4& rhs)
	{
		float result = 0;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			result += lhs[i] * rhs[i];
		}

		return result;
	}

	float length(const vec4& vec)
	{
		return sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2]) + (vec[3] * vec[3]));
	}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


	float no_sign_cofactor(const mat3& mat, std::pair<int, int> point)		//<**************
	{
		//EIKO PAREMPAA KEINOA!!!
		float result = 0.0;
		std::array<float, 4> elements = { 0,0,0,0 };
		int count = 0;

		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				if (i != point.first && j != point.second)
				{
					elements[count] = mat[i][j];
					count++;
				}
			}
		}
		result = elements[0] * elements[3] - elements[1] * elements[2];

		return result;
	}

	float no_sign_cofactor(const mat4& mat, std::pair<int, int> point)		//<**************
	{
		//EIKO PAREMPAA KEINOA!!!
		float result = 0.0;

		std::array<float, 9> elementsV = {0,0,0, 0,0,0, 0,0,0};
		int count = 0;

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				if (i != point.first && j != point.second)
				{
					elementsV[count] = mat[i][j];
					count++;
				}
			}
		}

		mat3 elementsM = {
			vec3({elementsV[0],elementsV[1],elementsV[2]}),
			vec3({elementsV[3],elementsV[4],elementsV[5]}),
			vec3({elementsV[6],elementsV[7],elementsV[8]})
		};

		result = det(elementsM);

		return result;
	}

	mat3 mul(const float mul, const mat3& mat)		//<**************
	{
		mat3 result = {
		vec3({0,0,0}),
		vec3({0,0,0}),
		vec3({0,0,0})
		};

		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				float val = mat[i][j] * mul;
				result[i][j] = val;
			}
		}

		return result;
	}

	float det(const mat3& mat)										//<**************
	{

		float result = 0;

		vec3 cofactors({ 0,0,0 });
		for (size_t i = 0; i < mat.size(); i++)
		{
			cofactors[i] = no_sign_cofactor(mat, { 0, i });
		}

		result = +mat[0][0] * cofactors[0] - mat[0][1] * cofactors[1] + mat[0][2] * cofactors[2];

		return result;
	}

	mat3 transpose(const mat3& mat)
	{
		vec3 v1;
		vec3 v2;
		vec3 v3;
		int index = 0;

		for (vec3 vec : mat)
		{
			v1[index] = vec[0];
			v2[index] = vec[1];
			v3[index] = vec[2];
			index++;
		}

		//glm::transpose(mat);  <- ei glm funktioita
		return mat3({v1,v2,v3});
	}

	mat3 inverse(const mat3& mat)
	{
		float determinant = det(mat);

		if (determinant == 0.0f)
		{
			throw std::runtime_error("Determinant is zero");
		}

		mat3 cofactormat = {
		vec3({+no_sign_cofactor(mat,{0,0}),-no_sign_cofactor(mat,{0,1}),+no_sign_cofactor(mat,{0,2})}),
		vec3({-no_sign_cofactor(mat,{1,0}),+no_sign_cofactor(mat,{1,1}),-no_sign_cofactor(mat,{1,2})}),
		vec3({+no_sign_cofactor(mat,{2,0}),-no_sign_cofactor(mat,{2,1}),+no_sign_cofactor(mat,{2,2})})
		};

		mat3 adjungate = transpose(cofactormat);

		

		//cofactor function
		//adjungate
		//pitaako olla myos jokin invert tai sen tyyppinen funktio
		
		float multiplier = (1.0f / determinant);

		//multiplier = roundDecimal(multiplier,4);

		mat3 result = mul(multiplier, adjungate);

		round(result);

		return result;
	}

	mat3 mul(const mat3& lhs, const mat3& rhs)
	{
		mat3 resultmatr;
		for (size_t i = 0; i < lhs.size(); i++)
		{
			vec3 resultvec;
			for (size_t j = 0; j < lhs.size(); j++)
			{
				float member1 = lhs[i][0] * rhs[0][j];
				float member2 = lhs[i][1] * rhs[1][j];
				float member3 = lhs[i][2] * rhs[2][j];

				resultvec[j] = member1 + member2 + member3;
			}
			resultmatr[i] = resultvec;
		}
		
		return resultmatr;
	}

	vec2 mul(const mat3& lhs, const vec2& rhs)
	{
		vec3 result;
		vec2 homogenousresult;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			vec2 momentarylhs({ lhs[i][0], lhs[i][1] });
			result[i] = (dot(momentarylhs, rhs) + lhs[i][2]);
			//dot(vec2) + 
		}
		homogenousresult = vec2({ result[0], result[1] });
		return homogenousresult;
	}

	vec3 mul(const mat3& lhs, const vec3& rhs)
	{
		vec3 result;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			vec3 momentarylhs({ lhs[i][0], lhs[i][1], lhs[i][2] });
			result[i] = dot(momentarylhs, rhs);
		}

		return result;
	}

	mat3 scaling(const vec2& scale)
	{
		mat3 identity = math::createIdentity<3>();

		mat3 result = identity;

		for (size_t i = 0; i < scale.size(); i++)
		{ result[i][i] = scale[i]; }

		return result;
	}

	mat3 translation(const vec2& position)
	{
		mat3 identity = math::createIdentity<3>();
		mat3 result = identity;

		for (size_t i = 0; i < position.size(); i++)
		{
			result[i][2] = position[i];
		}

		return result;
	}

	mat3 rotation(float radians)
	{
		return mat3({
			vec3({roundDecimal(cosf(radians),4),	roundDecimal(-sinf(radians),4),	0}),
			vec3({roundDecimal(sinf(radians),4),	roundDecimal(cosf(radians),4),	0}),
			vec3({0,				0,				1})
			});
	}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

	float det(const mat4& mat)									//<-------------------------
	{
		float result = 0.0f;
		vec4 cofactors({ 0,0,0,0 });

		for (size_t i = 0; i < mat.size(); i++)
		{
			cofactors[i] = no_sign_cofactor(mat, { 0, i });
		}

		result = +mat[0][0] * cofactors[0] - mat[0][1] * cofactors[1] + mat[0][2] * cofactors[2] - mat[0][3] * cofactors[3];

		return result;
	}

	mat4 transpose(const mat4& mat)
	{
		vec4 v1;
		vec4 v2;
		vec4 v3;
		vec4 v4;
		int index = 0;

		for (vec4 vec : mat)
		{
			v1[index] = vec[0];
			v2[index] = vec[1];
			v3[index] = vec[2];
			v4[index] = vec[3];
			index++;
		}

		//glm::transpose(mat);  <- ei glm funktioita
		return mat4({ v1,v2,v3,v4 });
	}

	mat4 mul(const mat4& lhs, const mat4& rhs)
	{
		mat4 resultmatr;
		for (size_t i = 0; i < lhs.size(); i++)
		{
			vec4 resultvec;
			for (size_t j = 0; j < lhs.size(); j++)
			{
				float member1 = lhs[i][0] * rhs[0][j];
				float member2 = lhs[i][1] * rhs[1][j];
				float member3 = lhs[i][2] * rhs[2][j];
				float member4 = lhs[i][3] * rhs[3][j];

				resultvec[j] = member1 + member2 + member3 + member4;
			}
			resultmatr[i] = resultvec;
		}

		return resultmatr;
	}

	vec3 mul(const mat4& lhs, const vec3& rhs)
	{
		vec4 result;
		vec3 homogenousresult;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			vec3 momentarylhs({ lhs[i][0], lhs[i][1], lhs[i][2]});
			result[i] = (dot(momentarylhs, rhs) + lhs[i][3]);
			//dot(vec2) + 
		}
		homogenousresult = vec3({ result[0], result[1],result[2] });
		return homogenousresult;
	}

	vec4 mul(const mat4& lhs, const vec4& rhs)
	{
		vec4 result;

		for (size_t i = 0; i < lhs.size(); i++)
		{
			vec4 momentarylhs({ lhs[i][0], lhs[i][1], lhs[i][2], lhs[i][3] });
			result[i] = dot(momentarylhs, rhs);
		}

		return result;
	}

	mat4 float_to_mat4(float f)
	{
		return mat4({
			vec4({ f,f,f,f }), vec4({ f,f,f,f }), vec4({ f,f,f,f }), vec4({ f,f,f,f })
			});
	}

	mat4 inverse(const mat4& mat)								//<-------------------------
	{
		float determinant = det(mat);

		if (determinant == 0.0f)
		{
			throw std::runtime_error("Determinant is zero");
		}

		mat4 cofactormat = {
			+no_sign_cofactor(mat,{0,0}), -no_sign_cofactor(mat,{0,1}), +no_sign_cofactor(mat,{0,2}), -no_sign_cofactor(mat,{0,3}),
			-no_sign_cofactor(mat,{1,0}), +no_sign_cofactor(mat,{1,1}), -no_sign_cofactor(mat,{1,2}), +no_sign_cofactor(mat,{1,3}),
			+no_sign_cofactor(mat,{2,0}), -no_sign_cofactor(mat,{2,1}), +no_sign_cofactor(mat,{2,2}), -no_sign_cofactor(mat,{2,3}),
			-no_sign_cofactor(mat,{3,0}), +no_sign_cofactor(mat,{3,1}), -no_sign_cofactor(mat,{3,2}), +no_sign_cofactor(mat,{3,3}),
		};

		mat4 adjungate = transpose(cofactormat);

		float multiplierf = (1.0f / determinant);
		/*mat4 multiplierm = float_to_mat4(multiplierf);
		mat4 identity = math::createIdentity<4>();
		multiplierm = mul(identity,multiplierm);*/
		mat4 scalar = scaling(multiplierf);


		mat4 result = mul(scalar, adjungate);
		round(result);

		return result;
	}

	mat4 scaling(float uniformScale)
	{
		mat4 identity = math::createIdentity<4>();

		mat4 result = identity;

		for (size_t i = 0; i < result.size(); i++)
		{
			result[i][i] = uniformScale;
		}

		return result;
	}

	mat4 scaling(const vec3& scale)
	{
		mat4 identity = math::createIdentity<4>();

		mat4 result = identity;

		for (size_t i = 0; i < scale.size(); i++)
		{
			result[i][i] = scale[i];
		}

		return result;
	}

	mat4 translation(const vec3& position)
	{
		mat4 identity = math::createIdentity<4>();
		mat4 result = identity;

		for (size_t i = 0; i < position.size(); i++)
		{
			result[i][3] = position[i];
		}

		return result;
	}

	mat4 rotationX(float radians)
	{
		return mat4({
			vec4({1,	0,								0,								0}),
			vec4({0,	roundDecimal(cosf(radians),4),	roundDecimal(-sinf(radians),4),	0}),
			vec4({0,	roundDecimal(sinf(radians),4),	roundDecimal(cosf(radians),4),	0}),
			vec4({0,	0,								0,								1})
			});
	}

	mat4 rotationY(float radians)
	{
		return mat4({
			vec4({roundDecimal(cosf(radians),4),	0,	roundDecimal(sinf(radians),4),	0}),
			vec4({0,								1,	0,								0}),
			vec4({roundDecimal(-sinf(radians),4),	0,	roundDecimal(cosf(radians),4),	0}),
			vec4({0,								0,	0,								1})
			});
	}

	mat4 rotationZ(float radians)
	{
		return mat4({
			vec4({roundDecimal(cosf(radians),4),	roundDecimal(-sinf(radians),4),	0,	0}),
			vec4({roundDecimal(sinf(radians),4),	roundDecimal(cosf(radians),4),	0,	0}),
			vec4({0,								0,								1,	0}),
			vec4({0,								0,								0,	1})
			});
	}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

	float degrees(float radians)
	{
		float pi = 3.14159265359f;
		return radians * (180 / pi);
	}

	float radians(float degrees)
	{
		float pi = 3.14159265359f;
		return degrees * (pi / 180);
	}

	float roundDecimal(float numf, int decimal)
	{
		const float multiplier = std::pow(10.0, decimal);
		return std::round(numf * multiplier) / multiplier;
	}

	void round(mat3 &m)
	{
		for (vec3 &v : m)
		{
			for (float& f : v)
			{
				f = roundDecimal(f,4);
			}
		}
	}

	void round(mat4& m)
	{
		for (vec4& v : m)
		{
			for (float& f : v)
			{
				f = roundDecimal(f, 4);
			}
		}
	}
	

	vec4 own_add(const vec4& lhs, const vec4& rhs)
	{
		__m128 LHS = _mm_set_ps(lhs[3], lhs[2], lhs[1], lhs[0]);
		__m128 RHS = _mm_set_ps(rhs[3], rhs[2], rhs[1], rhs[0]);

		__m128 result = _mm_add_ps(LHS,RHS);

		vec4 returnable;

		_mm_storeu_ps(returnable.data(), result);

		return returnable;
	}

	vec4 own_sub(const vec4& lhs, const vec4& rhs)
	{
		__m128 LHS = _mm_set_ps(lhs[3], lhs[2], lhs[1], lhs[0]);
		__m128 RHS = _mm_set_ps(rhs[3], rhs[2], rhs[1], rhs[0]);

		__m128 result = _mm_sub_ps(LHS, RHS);

		vec4 returnable;

		_mm_storeu_ps(returnable.data(), result);

		return returnable;
	}

	vec4 own_mul(float lhs, const vec4& rhs)
	{
		__m128 LHS = _mm_set_ps(lhs, lhs, lhs, lhs);
		__m128 RHS = _mm_set_ps(rhs[3], rhs[2], rhs[1], rhs[0]);

		__m128 result = _mm_mul_ps(LHS, RHS);

		vec4 returnable;

		_mm_storeu_ps(returnable.data(), result);

		return returnable;
	}

	vec4 own_mul(const vec4& lhs, float rhs)
	{
		return own_mul(rhs, lhs);
	}

	vec4 own_div(const vec4& lhs, float rhs)
	{
		__m128 LHS = _mm_set_ps(lhs[3], lhs[2], lhs[1], lhs[0]);
		__m128 RHS = _mm_set_ps(rhs, rhs, rhs, rhs);

		__m128 result = _mm_div_ps(LHS, RHS);

		vec4 returnable;

		_mm_storeu_ps(returnable.data(), result);

		return returnable;
	}

	/*float own_dot(const vec4& lhs, const vec4& rhs)
	{
		__m128 LHS = _mm_set_ps(lhs[3], lhs[2], lhs[1], lhs[0]);
		__m128 RHS = _mm_set_ps(rhs[3], rhs[2], rhs[1], rhs[0]);


		__m128 result = _mm_dp_ps(LHS, RHS, 0xF1);

		float returnable = _mm_cvtss_f32(result);

		return returnable;
	}*/
}