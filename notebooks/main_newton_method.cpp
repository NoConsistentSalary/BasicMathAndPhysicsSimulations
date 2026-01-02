#include <stdio.h>
#include <iostream>
#include <mikroplot/window.h>
#include <fstream>//ofstream
#include <thread>
#include <cmath>


template<typename T>
auto derive(T x, auto F)
{
	T h = 0.001;
	return (F(x+h) - F(x)) / h;
}

void drawFunctionAndItsDerivative(mikroplot::Window &window, auto F)
{
	//funktio
	window.drawFunction(F, 12, 2);
	//derivaatta
	window.drawFunction([F](float x) {
		return derive(x, F);
		} , 13, 2);
}

static inline bool isZero(float x)
{
	return abs(x - 0) < 0.001f;
}

static inline auto newtonsIteration(auto F, float x0)
{
	if (isZero(derive(x0, F))) return x0;

	return x0 - (F(x0) / derive(x0, F));
}


static const auto factorial(int x)
{
	if (x <= 1) return x;

	return x * factorial(x - 1);
}

static const float  exponent_impl(float x, int n)
{
	if (n == 0) return 1;

	return exponent_impl(x,n-1) + (pow(x,n)/factorial(n));
}

static const auto  myExp(float x)
{
	return exponent_impl(x, 10);
}

//auto derivativeDescent(auto F, float x0)
//{
//	float learningRate = 0.01f;
//	return x0 - learningRate * derive(x0,F);
//}

int main()
{
	static const auto myfunc1 = [](float x) {
		return (2*x*x*x) + (3*x*x)+0.5f;
		};

	static const auto myfunc2 = [](float x) {
		return exp(-x*0.05f) * 2.0f* cosf(x);
		};

	float x0 = -10.0f; // alkuarvaus
	float FLOAT_TOLERANCE = 0.01f;

	static const auto dmyfunc = [](float x) {
		return derive(x, myfunc1);
		};

	

	

	mikroplot::Window window(800, 800, "NB - Newton Rhapsody");

	window.update();
	while (false == window.shouldClose())
	{
		window.setScreen(-10, 10, -10, 10);
		window.drawAxis();

		drawFunctionAndItsDerivative(window, myfunc1);

		float x1 = newtonsIteration(myfunc1, x0);

		if (abs(x1-x0) < FLOAT_TOLERANCE)
		{
			printf("juuri loytynyt: x=%f, F(x)=%f",x1, myfunc1(x1));
			window.drawPoints({ {x1,myfunc1(x1)} }, 11, 8);
			window.update();
			break;
		}
		else
		{
			x0 = x1;//juurta ei loytynyt
		}

		//derivativeDescent
		printf("x0 nyt: %f\n", x0);//funktion nollakohta

		window.update();

		using namespace std::chrono_literals;
		std::this_thread::sleep_for(100ms);
	}

	using namespace std::chrono_literals;
	std::this_thread::sleep_for(5000ms);

	return 0;
}