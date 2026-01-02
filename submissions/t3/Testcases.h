#pragma once

#include "math.h"
#include <variant>
#include <vector>

using variant_type = std::variant<float, math::vec2, math::vec3, math::vec4, math::mat3, math::mat4>;

struct Testcase
{
	variant_type arg1;
	variant_type arg2;
	variant_type expOut;
};



//-----------------------------------------------------------------
//						Vec2 Testcases
//-----------------------------------------------------------------

const std::vector < std::vector<Testcase> > TestcasesV2 =
{

	//for addition
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::vec2({ 1,  1 }), math::vec2({ 2,  2 }), math::vec2({ 3,  3 })}),
		Testcase({math::vec2({ -1,  1 }), math::vec2({  1, -1 }), math::vec2({ 0,  0 })}),
		Testcase({math::vec2({ 4,  5 }), math::vec2({ -2,  3 }), math::vec2({ 2,  8 })}),
		Testcase({math::vec2({ 0,  0 }), math::vec2({ 0,  0 }), math::vec2({ 0,  0 })}),
		Testcase({math::vec2({ 1.5, 2.5 }), math::vec2({ 3.5, 1.5 }), math::vec2({ 5.0, 4.0 })}),
	},

	//for subtraction
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::vec2({ 4,  4 }), math::vec2({ 1,  1 }), math::vec2({ 3,  3 })}),
		Testcase({math::vec2({ 3,  3 }), math::vec2({ 2,  2 }), math::vec2({ 1,  1 })}),
		Testcase({math::vec2({ 0,  0 }), math::vec2({ -5,  5 }), math::vec2({ 5, -5 })}),
		Testcase({math::vec2({ 4,  5 }), math::vec2({ 2,  3 }), math::vec2({ 2,  2 })}),
		Testcase({math::vec2({ 1,  1 }), math::vec2({ 1,  1 }), math::vec2({ 0,  0 })}),
		Testcase({math::vec2({ 2.5, 1.5 }), math::vec2({ 1.5, 2.5 }), math::vec2({ 1.0, -1.0 })}),
	},

	//for multiplication0
	{
		//				arg1,               arg2,                  expOut
		Testcase({2.0f, math::vec2({ 1,  1 }), math::vec2({ 2,  2 })}),
		Testcase({-1.5f, math::vec2({ 2,  3 }), math::vec2({ -3, -4.5f })}),
		Testcase({0.0f, math::vec2({ 4,  5 }), math::vec2({ 0, 0 })}),
		Testcase({1.0f, math::vec2({ -3, -3 }), math::vec2({ -3, -3 })}),
		Testcase({0.5f, math::vec2({ 2, 2 }), math::vec2({ 1, 1 })}),
	},

	//for multiplication1
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::vec2({ 1,  1 }), 3.0f, math::vec2({ 3,  3 })}),
		Testcase({math::vec2({ -2, 5 }), -2.0f, math::vec2({ 4, -10 })}),
		Testcase({math::vec2({ 0, 0 }), 1.0f, math::vec2({ 0, 0 })}),
		Testcase({math::vec2({ 2.5, 3.5 }), 2.0f, math::vec2({ 5.0, 7.0 })}),
		Testcase({math::vec2({ 4, -3 }), 0.5f, math::vec2({ 2, -1.5 })}),
	},

	//for division
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::vec2({ 4,  8 }), 2.0f, math::vec2({ 2,  4 })}),
		Testcase({math::vec2({ 0,  5 }), 1.0f, math::vec2({ 0,  5 })}),
		Testcase({math::vec2({ -10, -5 }), -5.0f, math::vec2({ 2, 1 })}),
		Testcase({math::vec2({ 6,  3 }), 3.0f, math::vec2({ 2, 1 })}),
		Testcase({math::vec2({ 1.5, 3.0 }), 0.5f, math::vec2({ 3.0, 6.0 })}),
	},

	//for dot
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::vec2({ 1,  2 }), math::vec2({ 3,  4 }), 11.0f}),
		Testcase({math::vec2({ -1,  0 }), math::vec2({ 0, -1 }), 0.0f}),
		Testcase({math::vec2({ 2.0, 3.0 }), math::vec2({ 4.0, 5.0 }), 23.0f}),
		Testcase({math::vec2({ 1.0, 1.0 }), math::vec2({ 1.0, 1.0 }), 2.0f}),
		Testcase({math::vec2({ -2, 3 }), math::vec2({ 5, -1 }), -13.0f}),
	},

	//for cross
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::vec2({ 1, 2 }), math::vec2({ 3, 4 }), -2.0f}),
		Testcase({math::vec2({ -1, -1 }), math::vec2({ 1, 1 }), 0.0f}),
		Testcase({math::vec2({ 2, 1 }), math::vec2({ 1, 2 }), 3.0f}),
		Testcase({math::vec2({ 0, 0 }), math::vec2({ 5, 5 }), 0.0f}),
		Testcase({math::vec2({ 5.5, -7.5 }), math::vec2({ -3.5, 2.5 }),-12.5f}),
	},

	//for lenght
	{
		//				arg1,               ignored,                  expOut
		Testcase({math::vec2({0.0f, 0.0f}),     0.0f,                  0.0f}),
		Testcase({math::vec2({3.0f, 4.0f}),     0.0f,                  5.0f}),
		Testcase({math::vec2({-3.0f, 4.0f}),    0.0f,                  5.0f}),
		Testcase({math::vec2({1.0f, -1.0f}),    0.0f,                  1.41421356f}),
		Testcase({math::vec2({-1.0f, -1.0f}),   0.0f,                  1.41421356f}),
	},

};

//-----------------------------------------------------------------
//						Vec3 Testcases
//-----------------------------------------------------------------

const std::vector < std::vector<Testcase> > TestcasesV3 =
{
	//for addition
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::vec3({ 1,  2,  3 }), math::vec3({ 4,  5,  6 }), math::vec3({ 5,  7,  9 })}),
		Testcase({math::vec3({ -1,  0,  1 }), math::vec3({  1, -1,  0 }), math::vec3({ 0, -1,  1 })}),
		Testcase({math::vec3({ 3.5,  2.5,  1.5 }), math::vec3({ 1.5,  3.5,  4.5 }), math::vec3({ 5.0,  6.0,  6.0 })}),
		Testcase({math::vec3({ 0,  0,  0 }), math::vec3({ 0,  0,  0 }), math::vec3({ 0,  0,  0 })}),
		Testcase({math::vec3({ 1, 2, 3 }), math::vec3({ -1, -2, -3 }), math::vec3({ 0, 0, 0 })}),
	},

	//for subtraction
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::vec3({ 5,  7,  9 }), math::vec3({ 4,  5,  6 }), math::vec3({ 1,  2,  3 })}),
		Testcase({math::vec3({ 0,  0,  0 }), math::vec3({ 1,  1,  1 }), math::vec3({ -1, -1, -1 })}),
		Testcase({math::vec3({ 3,  3,  3 }), math::vec3({ 1,  1,  1 }), math::vec3({ 2,  2,  2 })}),
		Testcase({math::vec3({ -1, -2, -3 }), math::vec3({ -2, -3, -4 }), math::vec3({ 1,  1,  1 })}),
		Testcase({math::vec3({ 2.5, 3.0, 1.5 }), math::vec3({ 1.0, 1.0, 1.5 }), math::vec3({ 1.5, 2.0, 0.0 })}),
	},

	//for multiplication0
	{
		//				arg1,               arg2,                  expOut
		Testcase({2.0f, math::vec3({ 1,  2,  3 }), math::vec3({ 2,  4,  6 })}),
		Testcase({-1.5f, math::vec3({ 2,  3,  4 }), math::vec3({ -3, -4.5, -6 })}),
		Testcase({0.0f, math::vec3({ 4,  5,  6 }), math::vec3({ 0, 0, 0 })}),
		Testcase({1.0f, math::vec3({ -3, -3, -3 }), math::vec3({ -3, -3, -3 })}),
		Testcase({0.5f, math::vec3({ 2, 3, 4 }), math::vec3({ 1, 1.5, 2 })}),
	},

	//for multiplication1
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::vec3({ 1,  2,  3 }), 3.0f, math::vec3({ 3,  6,  9 })}),
		Testcase({math::vec3({ -2, 5, 1 }), -2.0f, math::vec3({ 4, -10, -2 })}),
		Testcase({math::vec3({ 0, 0, 0 }), 1.0f, math::vec3({ 0, 0, 0 })}),
		Testcase({math::vec3({ 2.5, 3.5, 4.5 }), 2.0f, math::vec3({ 5.0, 7.0, 9.0 })}),
		Testcase({math::vec3({ 4, -3, 2 }), 0.5f, math::vec3({ 2, -1.5, 1 })}),
	},

	//for division
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::vec3({ 4,  8,  12 }), 2.0f, math::vec3({ 2,  4,  6 })}),
		Testcase({math::vec3({ 0,  5,  10 }), 5.0f, math::vec3({ 0, 1, 2 })}),
		Testcase({math::vec3({ -10, -20, -30 }), -5.0f, math::vec3({ 2, 4, 6 })}),
		Testcase({math::vec3({ 6,  9,  12 }), 3.0f, math::vec3({ 2, 3, 4 })}),
		Testcase({math::vec3({ 1.5, 3.0, 4.5 }), 0.5f, math::vec3({ 3.0, 6.0, 9.0 })}),
	},

	//for dot
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::vec3({ 1,  2,  3 }), math::vec3({ 4,  5,  6 }), 32.0f}),
		Testcase({math::vec3({ -1, 0, 1 }), math::vec3({ 0, -1, 2 }), 2.0f}),
		Testcase({math::vec3({ 2.0, 3.0, 4.0 }), math::vec3({ 5.0, 6.0, 7.0 }), 56.0f}),
		Testcase({math::vec3({ 1.0, 1.0, 1.0 }), math::vec3({ 1.0, 1.0, 1.0 }), 3.0f}),
		Testcase({math::vec3({ -2, 3, 1 }), math::vec3({ 5, -1, 2 }), -11.0f}),
	},

	//for cross
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::vec3({ 1, 2, 3 }), math::vec3({ 4, 5, 6 }), math::vec3({ -3, 6, -3 })}),
		Testcase({math::vec3({ 0, 0, 0 }), math::vec3({ 1, 1, 1 }), math::vec3({ 0, 0, 0 })}),
		Testcase({math::vec3({ 2, 3, 4 }), math::vec3({ 5, 6, 7 }), math::vec3({ -3, 6, -3 })}),
		Testcase({math::vec3({ -1, -2, -3 }), math::vec3({ 1, 2, 3 }), math::vec3({ 0, 0, 0 })}),
		Testcase({math::vec3({ 3.5, 2.5, 1.5 }), math::vec3({ -1.5, -2.5, -3.5 }), math::vec3({ -5, 10, -5 })}),
	},

	//for lenght
	{
		Testcase({math::vec3({0.0f, 0.0f, 0.0f}),    0.0f,                 0.0f}),
		Testcase({math::vec3({1.0f, 2.0f, 2.0f}),    0.0f,                 3.0f}),
		Testcase({math::vec3({-1.0f, 2.0f, 2.0f}),   0.0f,                 3.0f}),
		Testcase({math::vec3({3.0f, 4.0f, 12.0f}),   0.0f,                13.0f}),
		Testcase({math::vec3({-3.0f, -4.0f, -12.0f}), 0.0f,                13.0f})
	},
};

//-----------------------------------------------------------------
//						Vec4 Testcases
//-----------------------------------------------------------------

const std::vector < std::vector<Testcase> > TestcasesV4 =
{
	//for addition
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::vec4({ 1,  2,  3,  4 }), math::vec4({ 5,  6,  7,  8 }), math::vec4({ 6,  8,  10, 12 })}),
		Testcase({math::vec4({ -1,  0,  1,  2 }), math::vec4({  1, -1,  0,  4 }), math::vec4({ 0, -1, 1, 6 })}),
		Testcase({math::vec4({ 2.5, 3.5, 4.5, 5.5 }), math::vec4({ 1.5, 2.5, 3.5, 4.5 }), math::vec4({ 4.0, 6.0, 8.0, 10.0 })}),
		Testcase({math::vec4({ 0,  0,  0,  0 }), math::vec4({ 0,  0,  0,  0 }), math::vec4({ 0,  0,  0,  0 })}),
		Testcase({math::vec4({ 1, 2, 3, 4 }), math::vec4({ -1, -2, -3, -4 }), math::vec4({ 0, 0, 0, 0 })}),
	},

	//for subtraction
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::vec4({ 5,  7,  9, 11 }), math::vec4({ 4,  5,  6,  7 }), math::vec4({ 1,  2,  3,  4 })}),
		Testcase({math::vec4({ 0,  0,  0,  0 }), math::vec4({ 1,  1,  1,  1 }), math::vec4({ -1, -1, -1, -1 })}),
		Testcase({math::vec4({ 3,  3,  3,  3 }), math::vec4({ 1,  1,  1,  1 }), math::vec4({ 2,  2,  2,  2 })}),
		Testcase({math::vec4({ -1, -2, -3, -4 }), math::vec4({ -2, -3, -4, -5 }), math::vec4({ 1, 1, 1, 1 })}),
		Testcase({math::vec4({ 2.5, 3.5, 4.5, 5.5 }), math::vec4({ 1.0, 1.0, 1.0, 1.0 }), math::vec4({ 1.5, 2.5, 3.5, 4.5 })}),
	},

	//for multiplication0
	{
		//				arg1,               arg2,                  expOut
		Testcase({2.0f, math::vec4({ 1,  2,  3,  4 }), math::vec4({ 2,  4,  6,  8 })}),
		Testcase({-1.5f, math::vec4({ 2,  3,  4,  5 }), math::vec4({ -3, -4.5, -6, -7.5 })}),
		Testcase({0.0f, math::vec4({ 4,  5,  6,  7 }), math::vec4({ 0, 0, 0, 0 })}),
		Testcase({1.0f, math::vec4({ -3, -3, -3, -3 }), math::vec4({ -3, -3, -3, -3 })}),
		Testcase({0.5f, math::vec4({ 2, 3, 4, 5 }), math::vec4({ 1, 1.5, 2, 2.5 })}),

	},

	//for multiplication1
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::vec4({ 1,  2,  3,  4 }), 3.0f, math::vec4({ 3,  6,  9, 12 })}),
		Testcase({math::vec4({ -2, 5, 1, 3 }), -2.0f, math::vec4({ 4, -10, -2, -6 })}),
		Testcase({math::vec4({ 0, 0, 0, 0 }), 1.0f, math::vec4({ 0, 0, 0, 0 })}),
		Testcase({math::vec4({ 2.5, 3.5, 4.5, 5.5 }), 2.0f, math::vec4({ 5.0, 7.0, 9.0, 11.0 })}),
		Testcase({math::vec4({ 4, -3, 2, 1 }), 0.5f, math::vec4({ 2, -1.5, 1, 0.5 })}),
	},

	//for division
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::vec4({ 4, 8, 12, 16 }), 2.0f, math::vec4({ 2, 4, 6, 8 })}),
		Testcase({math::vec4({ 10, 20, 30, 40 }), 5.0f, math::vec4({ 2, 4, 6, 8 })}),
		Testcase({math::vec4({ -10, -20, -30, -40 }), -2.0f, math::vec4({ 5, 10, 15, 20 })}),
		Testcase({math::vec4({ 1, 2, 3, 4 }), 1.0f, math::vec4({ 1, 2, 3, 4 })}),
		Testcase({math::vec4({ 5, 10, 15, 20 }), 0.5f, math::vec4({ 10, 20, 30, 40 })}),
		Testcase({math::vec4({ 3, 6, 9, 12 }), 3.0f, math::vec4({ 1, 2, 3, 4 })}),
	},

	//for dot
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::vec4({ 1, 2, 3, 4 }), math::vec4({ 2, 3, 4, 5 }), 40.0f}),
		Testcase({math::vec4({ 0, 0, 0, 0 }), math::vec4({ 0, 0, 0, 0 }), 0.0f}),
		Testcase({math::vec4({ -1, -2, -3, -4 }), math::vec4({ -5, -6, -7, -8 }), 70.0f}),
		Testcase({math::vec4({ 1, 0, 0, 0 }), math::vec4({ 0, 1, 0, 0 }), 0.0f}),
		Testcase({math::vec4({ 1, 2, 3, 4 }), math::vec4({ 5, 6, 7, 8 }), 70.0f}),
	},

	//for lenght
	{
		Testcase({math::vec4({0.0f, 0.0f, 0.0f, 0.0f}), 0.0f,              0.0f}),
		Testcase({math::vec4({1.0f, 2.0f, 2.0f, 2.0f}), 0.0f,              3.60555127f}),
		Testcase({math::vec4({-1.0f, 2.0f, 2.0f, 2.0f}), 0.0f,             3.60555127f}),
		Testcase({math::vec4({3.0f, 4.0f, 12.0f, 5.0f}), 0.0f,             13.92838827f}),
		Testcase({math::vec4({-3.0f, -4.0f, -12.0f, -5.0f}), 0.0f,         13.92838827f})
	},
};

//-----------------------------------------------------------------
//						Mat3 Testcases
//-----------------------------------------------------------------

const std::vector < std::vector<Testcase> > TestcasesM3 =
{

	//for determinant
	{
		//				arg1,     arg2-ignored,   expOut
		Testcase({math::mat3({ math::vec3({1, 2, 3}), math::vec3({0, 4, 5}), math::vec3({1, 0, 6}) }), 0.0f, 22.0f}),
		Testcase({math::mat3({ math::vec3({2, 5, 3}), math::vec3({1, -1, 4}), math::vec3({3, 3, 5}) }), 0.0f, 19.0f}),
		Testcase({math::mat3({ math::vec3({0, 0, 0}), math::vec3({0, 0, 0}), math::vec3({0, 0, 0}) }), 0.0f, 0.0f}),
		Testcase({math::mat3({ math::vec3({1, 2, 1}), math::vec3({1, 3, 2}), math::vec3({1, 0, 4}) }), 0.0f, 5.0f}),
		Testcase({math::mat3({ math::vec3({3, -1, 2}), math::vec3({2, 0, 1}), math::vec3({-1, 1, 2}) }), 0.0f, 6.0f}),
	},

	//for transpose
	{
		//				arg1,    arg2-ignored,     expOut
		Testcase({math::mat3({ math::vec3({1, 2, 3}), math::vec3({4, 5, 6}), math::vec3({7, 8, 9}) }), 0.0f, math::mat3({ math::vec3({1, 4, 7}), math::vec3({2, 5, 8}), math::vec3({3, 6, 9}) })}),
		Testcase({math::mat3({ math::vec3({0, 1, 2}), math::vec3({3, 4, 5}), math::vec3({6, 7, 8}) }), 0.0f, math::mat3({ math::vec3({0, 3, 6}), math::vec3({1, 4, 7}), math::vec3({2, 5, 8}) })}),
		Testcase({math::mat3({ math::vec3({1, 0, 0}), math::vec3({0, 2, 0}), math::vec3({0, 0, 3}) }), 0.0f, math::mat3({ math::vec3({1, 0, 0}), math::vec3({0, 2, 0}), math::vec3({0, 0, 3}) })}),
		Testcase({math::mat3({ math::vec3({2, 3, 5}), math::vec3({7, 11, 6}), math::vec3({13, 17, 19}) }), 0.0f, math::mat3({ math::vec3({2, 7, 13}), math::vec3({3, 11, 17}), math::vec3({5, 6, 19}) })}),
		Testcase({math::mat3({ math::vec3({1, -2, 3}), math::vec3({4, -5, 6}), math::vec3({7, -8, 9}) }), 0.0f, math::mat3({ math::vec3({1, 4, 7}), math::vec3({-2, -5, -8}), math::vec3({3, 6, 9}) })}),
	},

	//for inverse
	{
		//				arg1     arg2-ignored,       expOut
		Testcase({math::mat3({ math::vec3({1, 2, 3}), math::vec3({0, 1, 4}), math::vec3({5, 6, 0}) }), 0.0f,
			math::mat3({ math::vec3({-24, 18, 5}), math::vec3({20, -15, -4}), math::vec3({-5, 4, 1}) })}),
		Testcase({math::mat3({ math::vec3({2, 3, 1}), math::vec3({1, 4, 2}), math::vec3({3, 1, 5}) }), 0.0f,
			math::mat3({ math::vec3({0.6429, -0.5, 0.0714}), math::vec3({0.0357, 0.25, -0.1071}), math::vec3({-0.3929, 0.25, 0.1786}) })}),
		Testcase({math::mat3({ math::vec3({1, 0, 0}), math::vec3({0, 1, 0}), math::vec3({0, 0, 1}) }), 0.0f,
			math::mat3({ math::vec3({1, 0, 0}), math::vec3({0, 1, 0}), math::vec3({0, 0, 1}) })}),
		Testcase({math::mat3({ math::vec3({2, 5, 3}), math::vec3({1, -1, 4}), math::vec3({3, 3, 5}) }), 0.0f,
			math::mat3({ math::vec3({-0.8947, -0.8421, 1.2105}), math::vec3({0.3684, 0.0526, -0.2632}), math::vec3({0.3158, 0.4737, -0.3684}) })}),
	},


	//for multiplication0
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::mat3({ math::vec3({1, 2, 3}), math::vec3({4, 5, 6}), math::vec3({7, 8, 9}) }),
			   math::mat3({ math::vec3({9, 8, 7}), math::vec3({6, 5, 4}), math::vec3({3, 2, 1}) }),
			   math::mat3({ math::vec3({30, 24, 18}), math::vec3({84, 69, 54}), math::vec3({138, 114, 90}) })}),
		Testcase({math::mat3({ math::vec3({1, 0, 0}), math::vec3({0, 1, 0}), math::vec3({0, 0, 1}) }),
			   math::mat3({ math::vec3({5, 5, 5}), math::vec3({5, 5, 5}), math::vec3({5, 5, 5}) }),
			   math::mat3({ math::vec3({5, 5, 5}), math::vec3({5, 5, 5}), math::vec3({5, 5, 5}) })}),
		Testcase({math::mat3({ math::vec3({2, 0, 1}), math::vec3({1, 3, 2}), math::vec3({0, 0, 1}) }),
			   math::mat3({ math::vec3({1, 2, 3}), math::vec3({4, 5, 6}), math::vec3({7, 8, 9}) }),
			   math::mat3({ math::vec3({9, 12, 15}), math::vec3({27, 33, 39}), math::vec3({7, 8, 9}) })}),
		Testcase({math::mat3({ math::vec3({1, 2, 3}), math::vec3({0, 1, 4}), math::vec3({5, 6, 0}) }),
			   math::mat3({ math::vec3({7, 8, 9}), math::vec3({1, 2, 3}), math::vec3({4, 5, 6}) }),
			   math::mat3({ math::vec3({21, 27, 33}), math::vec3({17, 22, 27}), math::vec3({41, 52, 63}) })}),
	},

	//for multiplication1
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::mat3({ math::vec3({1, 2, 3}), math::vec3({4, 5, 6}), math::vec3({7, 8, 9}) }),
			   math::vec2({1, 1}),
			   math::vec2({6, 15})}),
		Testcase({math::mat3({ math::vec3({0, 1, 2}), math::vec3({3, 4, 5}), math::vec3({6, 7, 8}) }),
			   math::vec2({2, 3}),
			   math::vec2({5, 23})}),
		Testcase({math::mat3({ math::vec3({1, 0, 0}), math::vec3({0, 1, 0}), math::vec3({0, 0, 1}) }),
			   math::vec2({5, 6}),
			   math::vec2({5, 6})}),
		Testcase({math::mat3({ math::vec3({2, 3, 1}), math::vec3({1, 4, 2}), math::vec3({3, 1, 5}) }),
			   math::vec2({0, 1}),
			   math::vec2({4, 6})}),
		Testcase({math::mat3({ math::vec3({3, 5, -2}), math::vec3({2, 1, 4}), math::vec3({0, -1, 2}) }),
			   math::vec2({6, 7}),
			   math::vec2({51, 23})}),
	},

	//for multiplication2
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::mat3({ math::vec3({1, 2, 3}), math::vec3({4, 5, 6}), math::vec3({7, 8, 9}) }),
			   math::vec3({1, 1, 1}),
			   math::vec3({6, 15, 24})}),
		Testcase({math::mat3({ math::vec3({2, 3, 1}), math::vec3({1, 4, 2}), math::vec3({3, 1, 5}) }),
			   math::vec3({0, 0, 1}),
			   math::vec3({1, 2, 5})}),
		Testcase({math::mat3({ math::vec3({0, 1, 2}), math::vec3({3, 4, 5}), math::vec3({6, 7, 8}) }),
			   math::vec3({1, 2, 3}),
			   math::vec3({8, 26, 44})}),
		Testcase({math::mat3({ math::vec3({1, 0, 0}), math::vec3({0, 1, 0}), math::vec3({0, 0, 1}) }),
			   math::vec3({5, 6, 7}),
			   math::vec3({5, 6, 7})}),
		Testcase({math::mat3({ math::vec3({3, -1, 2}), math::vec3({2, 0, 1}), math::vec3({-1, 1, 2}) }),
			   math::vec3({1, 2, 3}),
			   math::vec3({7, 5, 7})}),
	},

	//for scaling
	{
		//				arg1,    arg2-ignored    expOut
		Testcase({math::vec2({1, 2}), 0.0f, math::mat3({ math::vec3({1, 0, 0}), math::vec3({0, 2, 0}), math::vec3({0, 0, 1}) })}),
    	Testcase({math::vec2({2, 3}), 0.0f, math::mat3({ math::vec3({2, 0, 0}), math::vec3({0, 3, 0}), math::vec3({0, 0, 1}) })}),
    	Testcase({math::vec2({0, 0}), 0.0f, math::mat3({ math::vec3({0, 0, 0}), math::vec3({0, 0, 0}), math::vec3({0, 0, 1}) })}),
    	Testcase({math::vec2({4, 2}), 0.0f, math::mat3({ math::vec3({4, 0, 0}), math::vec3({0, 2, 0}), math::vec3({0, 0, 1}) })}),
    	Testcase({math::vec2({3, 1}), 0.0f, math::mat3({ math::vec3({3, 0, 0}), math::vec3({0, 1, 0}), math::vec3({0, 0, 1}) })}),
	},

	//for translation
	{
		//			arg1,       arg2-ignored,      expOut
		Testcase({math::vec2({1, 2}), 0.0f, math::mat3({ math::vec3({1, 0, 1}), math::vec3({0, 1, 2}), math::vec3({0, 0, 1}) })}),
		Testcase({math::vec2({-3, 5}), 0.0f, math::mat3({ math::vec3({1, 0, -3}), math::vec3({0, 1, 5}), math::vec3({0, 0, 1}) })}),
		Testcase({math::vec2({0, 0}), 0.0f, math::mat3({ math::vec3({1, 0, 0}), math::vec3({0, 1, 0}), math::vec3({0, 0, 1}) })}),
		Testcase({math::vec2({4, 1}), 0.0f, math::mat3({ math::vec3({1, 0, 4}), math::vec3({0, 1, 1}), math::vec3({0, 0, 1}) })}),
		Testcase({math::vec2({10, -5}), 0.0f, math::mat3({ math::vec3({1, 0, 10}), math::vec3({0, 1, -5}), math::vec3({0, 0, 1}) })}),
	},

	//for rotation
	{
		//	arg1-in rad,      arg2-ignored,                  expOut
		Testcase({0.0f, 0.0f, math::mat3({ math::vec3({1, 0, 0}), math::vec3({0, 1, 0}), math::vec3({0, 0, 1}) })}),
		Testcase({(3.14159f / 2.0f), 0.0f, math::mat3({ math::vec3({0, -1, 0}), math::vec3({1, 0, 0}), math::vec3({0, 0, 1}) })}),  // 90 degrees
		Testcase({3.14159f, 0.0f, math::mat3({ math::vec3({-1, 0, 0}), math::vec3({0, -1, 0}), math::vec3({0, 0, 1}) })}),    // 180 degrees
		Testcase({((3 * 3.14159f) / 2.0f), 0.0f, math::mat3({ math::vec3({0, 1, 0}), math::vec3({-1, 0, 0}), math::vec3({0, 0, 1}) })}), // 270 degrees
		Testcase({(3.14159f / 4.0f), 0.0f, math::mat3({ math::vec3({0.7071f, -0.7071f, 0}), math::vec3({0.7071f, 0.7071f, 0}), math::vec3({0, 0, 1}) })}), // 45 degrees
	},
};

//-----------------------------------------------------------------
//						Mat4 Testcases
//-----------------------------------------------------------------

const std::vector < std::vector<Testcase> > TestcasesM4 =
{
	//for determinant
	{
		//				arg1,               ignored,                  expOut
		Testcase({math::mat4({ math::vec4({1, 2, 3, 4}), math::vec4({0, 5, 6, 7}), math::vec4({1, 0, 8, 9}), math::vec4({0, 0, 0, 1}) }), 0.0f, 37.0f}),
		Testcase({math::mat4({ math::vec4({3, 2, 1, 0}), math::vec4({6, 5, 4, 3}), math::vec4({9, 8, 7, 6}), math::vec4({12, 11, 10, 9}) }), 0.0f, 0.0f}),
		Testcase({math::mat4({ math::vec4({1, 0, 0, 0}), math::vec4({0, 1, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) }), 0.0f, 1.0f}),
		Testcase({math::mat4({ math::vec4({4, -2, 1, 3}), math::vec4({3, 1, -1, 2}), math::vec4({2, 0, 1, 0}), math::vec4({1, 1, 1, 1}) }), 0.0f, 30.0f}),
		Testcase({math::mat4({ math::vec4({0, 0, 0, 0}), math::vec4({0, 0, 0, 0}), math::vec4({0, 0, 0, 0}), math::vec4({0, 0, 0, 0}) }), 0.0f, 0.0f}),
	},

	//for transpose
	{
		//				arg1,               ignored,                  expOut
		Testcase({math::mat4({ math::vec4({1, 2, 3, 4}), math::vec4({5, 6, 7, 8}), math::vec4({9, 10, 11, 12}), math::vec4({13, 14, 15, 16})}), 0.0f, math::mat4({ math::vec4({1, 5, 9, 13}), math::vec4({2, 6, 10, 14}), math::vec4({3, 7, 11, 15}), math::vec4({4, 8, 12, 16}) })}),
		Testcase({math::mat4({ math::vec4({0, 1, 2, 3}), math::vec4({4, 5, 6, 7}), math::vec4({8, 9, 10, 11}), math::vec4({12, 13, 14, 15})}), 0.0f, math::mat4({ math::vec4({0, 4, 8, 12}), math::vec4({1, 5, 9, 13}), math::vec4({2, 6, 10, 14}), math::vec4({3, 7, 11, 15}) })}),
		Testcase({math::mat4({ math::vec4({1, 0, 0, 0}), math::vec4({0, 1, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1})}), 0.0f, math::mat4({ math::vec4({1, 0, 0, 0}), math::vec4({0, 1, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) })}),
		Testcase({math::mat4({ math::vec4({2, 3, 5, 7}), math::vec4({11, 13, 17, 19}), math::vec4({23, 29, 31, 37}), math::vec4({41, 43, 47, 53})}), 0.0f, math::mat4({ math::vec4({2, 11, 23, 41}), math::vec4({3, 13, 29, 43}), math::vec4({5, 17, 31, 47}), math::vec4({7, 19, 37, 53}) })}),
	},

	//for inverse
	{
		//				arg1,               ignored,                  expOut
		Testcase({math::mat4({ math::vec4({1, 2, 3, 4}), math::vec4({0, 1, 2, 3}), math::vec4({0, 0, 1, 2}), math::vec4({0, 0, 0, 1})}), 0.0f, math::mat4({ math::vec4({1, -2, 1, 0}), math::vec4({0, 1, -2, 1}), math::vec4({0, 0, 1, -2}), math::vec4({0, 0, 0, 1}) })}),
		Testcase({math::mat4({ math::vec4({2, 5, 3, 1}), math::vec4({1, 4, 2, 3}), math::vec4({3, 1, 5, 2}), math::vec4({1, 2, 3, 1})}), 0.0f, math::mat4({ math::vec4({0.4130, -0.0652, 0.4565, -1.1304}), math::vec4({0.1957, 0.0217, -0.1522, 0.0435}), math::vec4({-0.1739, -0.1304, -0.0870, 0.7391}), math::vec4({-0.2826, 0.4130, 0.1087, -0.1739}) })}),
		Testcase({math::mat4({ math::vec4({3, 0, 0, 0}), math::vec4({0, 3, 0, 0}), math::vec4({0, 0, 3, 0}), math::vec4({0, 0, 0, 1})}), 0.0f, math::mat4({ math::vec4({0.3333, 0, 0, 0}), math::vec4({0, 0.3333, 0, 0}), math::vec4({0, 0, 0.3333, 0}), math::vec4({0, 0, 0, 1}) })}),
		
		Testcase({math::mat4({ math::vec4({1, 2, 1, 0}), math::vec4({2, 3, 1, 0}), math::vec4({1, 1, 1, 1}), math::vec4({0, 0, 0, 1})}), 0.0f, math::mat4({ math::vec4({-2, 1, 1, -1}), math::vec4({1, 0, -1, 1}), math::vec4({1, -1, 1, -1}), math::vec4({0, 0, 0, 1}) })}),
		Testcase({math::mat4({ math::vec4({4, 7, 2, 3}), math::vec4({3, 6, 1, 5}), math::vec4({1, 2, 3, 4}), math::vec4({0, 0, 0, 1})}), 0.0f, math::mat4({ math::vec4({2, -2.125, -0.625, 7.125}), math::vec4({-1, 1.25, 0.25, -4.25}), math::vec4({0, -0.125, 0.375, -0.875}), math::vec4({0, 0, 0, 1}) })}),
	},//

	//for multiplication0
	{
		//				arg1,               arg2,                  expOut
		Testcase({
				math::mat4({ math::vec4({1, 2, 3, 4}), math::vec4({5, 6, 7, 8}), math::vec4({9, 10, 11, 12}), math::vec4({13, 14, 15, 16}) }),
				math::mat4({ math::vec4({1, 0, 0, 0}), math::vec4({0, 1, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) }),
				math::mat4({ math::vec4({1, 2, 3, 4}), math::vec4({5, 6, 7, 8}), (math::vec4{9, 10, 11, 12}), math::vec4({13, 14, 15, 16}) })
			}),

		Testcase({
				math::mat4({ math::vec4({0, 1, 2, 3}), math::vec4({4, 5, 6, 7}), math::vec4({8, 9, 10, 11}), math::vec4({12, 13, 14, 15}) }),
				math::mat4({ math::vec4({1, 0, 0, 0}), math::vec4({0, 1, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) }),
				math::mat4({ math::vec4({0, 1, 2, 3}), math::vec4({4, 5, 6, 7}), math::vec4({8, 9, 10, 11}), math::vec4({12, 13, 14, 15}) })
			}),

		Testcase({
				math::mat4({ math::vec4({1, 2, 3, 4}), math::vec4({0, 1, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) }),
				math::mat4({ math::vec4({1, 1, 1, 1}), math::vec4({1, 1, 1, 1}), math::vec4({1, 1, 1, 1}), math::vec4({1, 1, 1, 1}) }),
				math::mat4({ math::vec4({10, 10, 10, 10}), math::vec4({1, 1, 1, 1}), math::vec4({1, 1, 1, 1}), math::vec4({1, 1, 1, 1}) })
			}),

		Testcase({
				math::mat4({ math::vec4({1, 2, 3, 4}), math::vec4({5, 6, 7, 8}), math::vec4({9, 10, 11, 12}), math::vec4({1, 1, 1, 1}) }),
				math::mat4({ math::vec4({1, 1, 1, 1}), math::vec4({0, 1, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) }),
				math::mat4({ math::vec4({1, 3, 4, 5}), math::vec4({5, 11, 12, 13}), math::vec4({9, 19, 20, 21}), math::vec4({1, 2, 2, 2}) })
			}),

		Testcase({
				math::mat4({ math::vec4({4, 2, 0, 1}), math::vec4({3, 5, 1, 2}), math::vec4({2, 1, 1, 3}), math::vec4({0, 0, 0, 1}) }),
				math::mat4({ math::vec4({1, 0, 0, 0}), math::vec4({0, 1, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) }),
				math::mat4({ math::vec4({4, 2, 0, 1}), math::vec4({3, 5, 1, 2}), math::vec4({2, 1, 1, 3}), math::vec4({0, 0, 0, 1}) })
			}),
	},

	//for multiplication1
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::mat4({ math::vec4({1, 2, 3, 4}), math::vec4({5, 6, 7, 8}), math::vec4({9, 10, 11, 12}), math::vec4({13, 14, 15, 16}) }),
			   math::vec3({1, 1, 1}),
			   math::vec3({ {10}, {26}, {42} })}),

		Testcase({math::mat4({ math::vec4({0, 1, 2, 3}), math::vec4({4, 5, 6, 7}), math::vec4({8, 9, 10, 11}), math::vec4({12, 13, 14, 15}) }),
			   math::vec3({1, 0, 1}),
			   math::vec3({ {5}, {17}, {29} })}),

		Testcase({math::mat4({ math::vec4({1, 0, 0, 0}), math::vec4({0, 1, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) }),
			   math::vec3({5, 6, 7}),
			   math::vec3({ {5}, {6}, {7} })}),

		Testcase({math::mat4({ math::vec4({2, 2, 2, 2}), math::vec4({1, 1, 1, 1}), math::vec4({0, 0, 0, 1}), math::vec4({0, 0, 0, 0}) }),
			   math::vec3({2, 3, 4}),
			   math::vec3({ {20}, {10}, {1} })}),

		Testcase({math::mat4({ math::vec4({3, -1, 2, 4}), math::vec4({2, 0, 1, 5}), math::vec4({-1, 1, 2, 3}), math::vec4({0, 0, 0, 1}) }),
			   math::vec3({1, 2, 3}),
			   math::vec3({ {11}, {10}, {10} })}),
	},

	//for multiplication2
	{
		//				arg1,               arg2,                  expOut
		Testcase({math::mat4({ math::vec4({1, 2, 3, 4}), math::vec4({5, 6, 7, 8}), math::vec4({9, 10, 11, 12}), math::vec4({13, 14, 15, 16}) }),
			   math::vec4({1, 1, 1, 1}),
			   math::vec4({ {10}, {26}, {42}, {58} })}),

		Testcase({math::mat4({ math::vec4({0, 1, 2, 3}), math::vec4({4, 5, 6, 7}), math::vec4({8, 9, 10, 11}), math::vec4({12, 13, 14, 15}) }),
			   math::vec4({1, 0, 1, 1}),
			   math::vec4({ {5}, {17}, {29}, {41} })}),

		Testcase({math::mat4({ math::vec4({1, 0, 0, 0}), math::vec4({0, 1, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) }),
			   math::vec4({5, 6, 7, 1}),
			   math::vec4({ {5}, {6}, {7}, {1} })}),

		Testcase({math::mat4({ math::vec4({2, 2, 2, 2}), math::vec4({1, 1, 1, 1}), math::vec4({0, 0, 0, 1}), math::vec4({0, 0, 0, 0}) }),
			   math::vec4({2, 3, 4, 1}),
			   math::vec4({ {20}, {10}, {1}, {0} })}),

		Testcase({math::mat4({ math::vec4({3, -1, 2, 4}), math::vec4({2, 0, 1, 5}), math::vec4({-1, 1, 2, 3}), math::vec4({0, 0, 0, 1}) }),
			   math::vec4({1, 2, 3, 1}),
			   math::vec4({ {11}, {10}, {10}, {1} })}),
	},

	//for scaling0
	{
		//		  arg1, ignored,                  expOut
		Testcase({ 2.0f, 0.0f, math::mat4({ math::vec4({2, 0, 0, 0}), math::vec4({0, 2, 0, 0}), math::vec4({0, 0, 2, 0}), math::vec4({0, 0, 0, 2}) })}),
		Testcase({ 3.0f, 0.0f, math::mat4({ math::vec4({3, 0, 0, 0}), math::vec4({0, 3, 0, 0}), math::vec4({0, 0, 3, 0}), math::vec4({0, 0, 0, 3}) })}), 
		Testcase({ 0.5f, 0.0f, math::mat4({ math::vec4({0.5f, 0, 0, 0}), math::vec4({0, 0.5f, 0, 0}), math::vec4({0, 0, 0.5f, 0}), math::vec4({0, 0, 0, 0.5f}) })}),
		Testcase({ 5.0f, 0.0f, math::mat4({ math::vec4({5.0f, 0, 0, 0}), math::vec4({0, 5.0f, 0, 0}), math::vec4({0, 0, 5.0f, 0}), math::vec4({0, 0, 0, 5.0f}) })}),
	},

	//for scaling1
	{
		//				arg1,               ignored,                  expOut
		Testcase({math::vec3({1, 2, 3}), 0.0f, math::mat4({ math::vec4({1, 0, 0, 0}), math::vec4({0, 2, 0, 0}), math::vec4({0, 0, 3, 0}), math::vec4({0, 0, 0, 1}) })}),
		Testcase({math::vec3({4, 5, 6}), 0.0f, math::mat4({ math::vec4({4, 0, 0, 0}), math::vec4({0, 5, 0, 0}), math::vec4({0, 0, 6, 0}), math::vec4({0, 0, 0, 1}) })}),
		Testcase({math::vec3({1, 1, 1}), 0.0f, math::mat4({ math::vec4({1, 0, 0, 0}), math::vec4({0, 1, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) })}),
		Testcase({math::vec3({0, 0, 0}), 0.0f, math::mat4({ math::vec4({0, 0, 0, 0}), math::vec4({0, 0, 0, 0}), math::vec4({0, 0, 0, 0}), math::vec4({0, 0, 0, 1}) })}),
		Testcase({math::vec3({-2, 3, 4}), 0.0f, math::mat4({ math::vec4({-2, 0, 0, 0}), math::vec4({0, 3, 0, 0}), math::vec4({0, 0, 4, 0}), math::vec4({0, 0, 0, 1}) })}),
	},

	//for translation
	{
		//				arg1,               ignored,                  expOut
		Testcase({math::vec3({1, 2, 3}), 0.0f, math::mat4({ math::vec4({1, 0, 0, 1}), math::vec4({0, 1, 0, 2}), math::vec4({0, 0, 1, 3}), math::vec4({0, 0, 0, 1}) })}),
		Testcase({math::vec3({-1, -2, -3}), 0.0f, math::mat4({ math::vec4({1, 0, 0, -1}), math::vec4({0, 1, 0, -2}), math::vec4({0, 0, 1, -3}), math::vec4({0, 0, 0, 1}) })}),
		Testcase({math::vec3({0, 0, 0}), 0.0f, math::mat4({ math::vec4({1, 0, 0, 0}), math::vec4({0, 1, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) })}),
		Testcase({math::vec3({2, 1, 0}), 0.0f, math::mat4({ math::vec4({1, 0, 0, 2}), math::vec4({0, 1, 0, 1}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) })}),
		Testcase({math::vec3({3, -4, 5}), 0.0f, math::mat4({ math::vec4({1, 0, 0, 3}), math::vec4({0, 1, 0, -4}), math::vec4({0, 0, 1, 5}), math::vec4({0, 0, 0, 1}) })}),
	},

	//for rotationx
	{
		//				arg1,               ignored,                  expOut
		Testcase({0.0f, 0.0f, math::mat4({ math::vec4({1, 0, 0, 0}), math::vec4({0, 1, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) })}), // 0 radians
		Testcase({1.5708f, 0.0f, math::mat4({ math::vec4({1, 0, 0, 0}), math::vec4({0, 0, -1, 0}), math::vec4({0, 1, 0, 0}), math::vec4({0, 0, 0, 1}) })}), // 90 degrees
		Testcase({3.14159f, 0.0f, math::mat4({ math::vec4({1, 0, 0, 0}), math::vec4({0, -1, 0, 0}), math::vec4({0, 0, -1, 0}), math::vec4({0, 0, 0, 1}) })}), // 180 degrees
		Testcase({4.71239f, 0.0f, math::mat4({ math::vec4({1, 0, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, -1, 0, 0}), math::vec4({0, 0, 0, 1}) })}), // 270 degrees
		Testcase({0.7854f, 0.0f, math::mat4({ math::vec4({1, 0, 0, 0}), math::vec4({0, 0.7071f, -0.7071f, 0}), math::vec4({0, 0.7071f, 0.7071f, 0}), math::vec4({0, 0, 0, 1}) })}), // 45 degrees
	},

	//for rotationy
	{
		//				arg1,               ignored,                  expOut
		Testcase({0.0f, 0.0f, math::mat4({ math::vec4({1, 0, 0, 0}), math::vec4({0, 1, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) })}), // 0 radians
		Testcase({1.5708f, 0.0f, math::mat4({ math::vec4({0, 0, 1, 0}), math::vec4({0, 1, 0, 0}), math::vec4({-1, 0, 0, 0}), math::vec4({0, 0, 0, 1}) })}), // 90 degrees
		Testcase({3.14159f, 0.0f, math::mat4({ math::vec4({-1, 0, 0, 0}), math::vec4({0, 1, 0, 0}), math::vec4({0, 0, -1, 0}), math::vec4({0, 0, 0, 1}) })}), // 180 degrees
		Testcase({4.71239f, 0.0f, math::mat4({ math::vec4({0, 0, -1, 0}), math::vec4({0, 1, 0, 0}), math::vec4({1, 0, 0, 0}), math::vec4({0, 0, 0, 1}) })}), // 270 degrees
		Testcase({0.7854f, 0.0f, math::mat4({ math::vec4({0.7071f, 0, 0.7071f, 0}), math::vec4({0, 1, 0, 0}), math::vec4({-0.7071f, 0, 0.7071f, 0}), math::vec4({0, 0, 0, 1}) })}), // 45 degrees
	},

	//for rotationz
	{
		//				arg1,               ignored,                  expOut
		Testcase({0.0f, 0.0f, math::mat4({ math::vec4({1, 0, 0, 0}), math::vec4({0, 1, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) })}), // 0 radians
		Testcase({1.5708f, 0.0f, math::mat4({ math::vec4({0, -1, 0, 0}), math::vec4({1, 0, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) })}), // 90 degrees
		Testcase({3.14159f, 0.0f, math::mat4({ math::vec4({-1, 0, 0, 0}), math::vec4({0, -1, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) })}), // 180 degrees
		Testcase({4.71239f, 0.0f, math::mat4({ math::vec4({0, 1, 0, 0}), math::vec4({-1, 0, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) })}), // 270 degrees
		Testcase({0.7854f, 0.0f, math::mat4({ math::vec4({0.7071f, -0.7071f, 0, 0}), math::vec4({0.7071f, 0.7071f, 0, 0}), math::vec4({0, 0, 1, 0}), math::vec4({0, 0, 0, 1}) })}), // 45 degrees
	},
};
