#include <stdio.h>
#include <iostream>
#include <mikroplot/window.h>
#include <fstream>//ofstream
#include <thread>
#include <cmath>

//namespace func
//{
//	template<typename T>
//	auto gen(size_t N, auto f)
//	{
//		std::vector<T> res;
//		for (size_t i = 0; i < N; i++)
//		{
//			res.push_back(f(i));
//		}
//		return res;
//	}
//}
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

int main()
{
	std::ofstream outfile("vastaukset.md");
	outfile << "# Vastaukset\n";
	outfile << "# Eetu Horttanainen\n";

	mikroplot::Window window(800, 800, "NB - Simple draw"); //pitaa olla talleen etta toimii kunnolla?



	auto pow2 = [](float x) {
		return x*x;
		};

	auto dpow2 = [pow2](float x) {
		return derive(x,pow2);// = 2x
		};

	auto sinifuncktio = [](float x) {
		return sinf(x);
		};

	auto siniamplitudi3funcktio = [](float x) {
		return 3.0f* sinf(x);
		};

	auto sini10ffunktio = [](float x) {
		return sinf(10.0f*x);
		};

	auto pow3 = [](float x) {
		return x*x*x;
		};

	
	auto ePOWx = [](float x) {
		return expf(x);// = 2x
		};
	//auto dcos = [pow2](float x) {
	//	return derive(x, pow2);// = 2x
	//	};


	std::vector<std::function<float(float)>> functions = {
		pow2,
		pow3,
		sinifuncktio,
		siniamplitudi3funcktio,
		sini10ffunktio,
		ePOWx
	};


	std::vector<std::string> functionNames = {
		"x^2","x^3","sin(x)","3*sin(x)", "sin(10*x)", "e^x"
	};

	int i = 0;

	//mikroplot::Window window(800, 800, "NB - Simple Draw");
	window.update();
	while (false == window.shouldClose())
	{
		window.setScreen(-10, 10, -10, 10);
		window.drawAxis();

		//draw x pow 2
		/*window.drawFunction([](float x) {
			x += 2.5f;
			return x * x + 1;
			}, 12, 4);*/

		//window.drawFunction(pow2,12,4);
		//window.drawFunction(pow3, 11, 2);
		//window.drawFunction(functions[2], 11, 2);
		//window.drawFunction(functions[3], 11, 2);
		//window.drawFunction(functions[4], 13, 2);

		//window.drawFunction(dpow2, 12, 2);

		//drawFunctionAndItsDerivative(window, functions[0]);
		drawFunctionAndItsDerivative(window, functions[i]);

		/*window.drawFunction([](float x){
			return 0.0f;
		}, 11, 2);*/

		window.update();

		std::string fileName = std::to_string(i) + ".png";
		window.screenshot(fileName);// vasta updaten jälkeen kirjoittaa png:n
		outfile << "Funktio: " + functionNames[i] << std::endl;
		outfile << "![](" + fileName + " \"Funktio:" + std::to_string(i) + "\")" << std::endl;
		//window.drawCircle({ 0,0 }, 3.0f);
		
		++i;

		if (i >=functions.size())
		{
			window.update();
			break;
		}
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(1000ms);
	}

	outfile.close();

	return 0;
}