#include <stdio.h>
#include <iostream>
#include <mikroplot/window.h>
#include <fstream>//ofstream
#include <thread>
#include <cmath>
#include <array>

//kun teet tehttavaa niin includaa headerista t3/my_math
//#include <my_math.h>
//

namespace math
{
	using vec2 = std::array<float, 2>;

	vec2 add(const vec2& lhs, const vec2& rhs)
	{
		vec2 result;
		/*result[0] = lhs[0] + rhs[0];
		result[1] = lhs[1] + rhs[1];*/

		for (size_t i = 0; i < lhs.size(); i++)
		{
			result[i] = lhs[i] + rhs[i];
		}

		return result;
	}

	vec2 mul(float k, const vec2& v)
	{
		vec2 result;
		
		//result[0] = k*v[0]
		//result[0] = k*v[1]

		for (size_t i = 0; i < v.size(); i++)
		{
			result[i] = k*v[i];
		}

		return result;
	}

	vec2 mul(const vec2& v, float k)
	{
		return mul(k,v);
	}


	float dot(const vec2& lhs, const vec2& rhs)
	{
		float result = 0;

		/*result += lhs[0] * rhs[0];
		result += lhs[1] * rhs[1];*/

		for (size_t i = 0; i < lhs.size(); i++)
		{
			result += lhs[i] * rhs[i];
		}

		return result;
	}

	auto len(auto v)
	{
		return sqrtf(dot(v, v));
	}

	auto normalize(auto v)
	{
		auto vecLen = len(v);
		auto invVecLen = 1.0f / vecLen;
		return mul(v,invVecLen);
	}


	static inline std::string to_String(const auto& v)
	{
		std::string res = "<";
		for (size_t i = 0; i < v.size(); i++)
		{
			res += std::to_string(v[i]) + " ";
		}
		if(res.size() > 0)
		{
			res.pop_back();
		}
		res += ">";
		return res;
	}

}


bool testFunc1(auto unitUnderTest, auto input, auto result)
{
	auto callResult = unitUnderTest(input);
	if (callResult == result)
	{
		return true;
	}

	printf("test failed\n");
	printf("   Expected result: %s\n", math::to_String(result).c_str());
	printf("   Got Reslut: %s\n", math::to_String(callResult).c_str());
	return false;
}

bool testFunc2(auto unitUnderTest, auto lhs, auto rhs, auto result)
{
	auto callResult = unitUnderTest(lhs, rhs);
	if (callResult == result)
	{
		return true;
	}

	printf("test failed\n");
	printf("   Expected result: %s\n", math::to_String(result).c_str());
	printf("   Got Reslut: %s\n", math::to_String(callResult).c_str());
	return false;
}

int main()
{

	using namespace math;

	printf("# Math test raport\n");

	vec2 a = {3,0};
	vec2 b = {1,4};

	printf("a = %s\n", to_String(a).c_str());
	printf("b = %s\n", to_String(b).c_str());

	auto aPlusb = add(a, b);
	printf("a + b = %s\n", to_String(aPlusb).c_str());

	if (false == testFunc2(math::add, vec2{3,0}, vec2{1,4}, vec2{4,4}))
	{
		return -1;
	}

	vec2 a1 = { 3,4 };

	if (len(a1) != 5.0f)
	{
		return -1;
	}

	//printf("len a1 = %f\n", len(a1));

	printf("vector a1 = %s\n", to_String(a1).c_str());
	auto normalizeA1 = normalize(a1);

	if (len(normalizeA1) != 1.0f)
	{
		printf("vector normalisation failed\n");
		return -1;
	}
	printf("vector a1 normalized = %s\n", to_String(normalizeA1).c_str());
	

	/*mikroplot::Window window(800, 800, "NB - Simple draw");

	window.update();

	while (false == window.shouldClose())
	{
		window.setScreen(-10, 10, -10, 10);
		window.drawAxis();
		window.update();
	}*/
	return 0;
}