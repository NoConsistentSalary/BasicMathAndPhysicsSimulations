#include <stdio.h>
#include <iostream>
#include <mikroplot/window.h>
#include <fstream>
#include <thread>
#include <cmath>

#include "FileWritingFunctions.h"


template<typename T>
auto derive(T x, auto F)
{
	//mika on pienin mahdollinen arvo jonka floatilla saa? <- onko parhain?
	T h = 0.001;//PIENEMPI NUMERO MAHDOLLISESTI?
	return (F(x + h) - F(x)) / h;
}

void drawFunctionAndItsDerivative(mikroplot::Window& window, auto F)
{
	//funktio
	window.drawFunction(F, 12, 2);
	//derivaatta
	window.drawFunction([F](float x) {
		return derive(x, F);
		}, 13, 2);
}

static inline bool isZero(float x)
{
	return abs(x - 0) < 0.001f;
}

static inline auto newtonsIteration(auto F, float x0)
{
	if (isZero(derive(x0, F))) return x0;//myos FLOAT_TOLERANCE?

	return x0 - (F(x0) / derive(x0, F));
}




int main()
{

	int function_index = 0;

	//The function lambdas, lists and names

	static const auto myfunc1 = [](float x)
		{
			return powf(x,3) -1;
		};
	
	static const auto myfunc2 = [](float x)
		{
			return cosf(x) - powf(x,3);
		};
	
	static const auto myfunc3 = [](float x)
		{
			return (powf(x, 4.0f) + 11.0f * powf(x, 3.0f) + 8 * powf(x, 2.0f) + 20.0f * x - 10.0f) / 1000.0f;
		};

	std::vector<std::function<float(float)>> functions = {
	myfunc1,
	myfunc2,
	myfunc3,
	};

	std::vector <std::string> functionNames = {
		"f(x) = x^3 - 1 kun x0 = 0.5",
		"f(x) = cos(x)-x^3 = 0 kun x0 = 0.5.",
		"f(x) = (x^4 + 11x^3 + 8x^2 + 20*x - 10) / 1000 minimi",
	};

	float x0 = 0.5f;
	float FLOAT_TOLERANCE = 0.0001f;

	static const auto dmyfunc = [](float x) {
		return derive(x, myfunc1);
		};

	//create filehandler and set up stuff
	FileHandler filehandler(__FILE__, "vastaukset.md");
	filehandler.writeLineInFile("# Vastaukset\n");
	filehandler.writeLineInFile("# Eetu Horttanainen\n");

	std::string filelocation = filehandler.getFilelocation();

	mikroplot::Window window(800, 800, "Numeerinen_Integrointi_Newtonin_Menetelmalla");

	window.update();
	while (false == window.shouldClose())
	{
		window.setScreen(-10, 10, -10, 10);
		window.drawAxis();

		drawFunctionAndItsDerivative(window, functions[function_index]);

		float x1 = newtonsIteration(functions[function_index], x0);

		if (abs(x1 - x0) < FLOAT_TOLERANCE)
		{
			printf("root found: x=%f, F(x)=%f\n", x1, functions[function_index](x1));
			window.drawPoints({ {x1,functions[function_index](x1)} }, 11, 8);

			window.update();

			//write into file
			std::string PNGfilename = std::to_string(function_index) + ".png";
			window.screenshot(filelocation + "\\" + PNGfilename);
			filehandler.writeLineInFile("Funktio: " + functionNames[function_index] + "\n\n");
			filehandler.writeLineInFile("Vastaus: " + std::to_string(x1) + "\n\n");
			filehandler.writeLineInFile(
				"![](" + PNGfilename + " \"Funktio:" + std::to_string(function_index) + "\")" + "\n\n"
			);

			function_index++;

			using namespace std::chrono_literals;
			std::this_thread::sleep_for(1500ms);

			//break;
		}
		else
		{
			x0 = x1;
		}

		

		//derivativeDescent
		printf("x0 nyt: %f\n", x0);//funktion nollakohta

		window.update();

		if (function_index >= functions.size())
		{
			break;
		}
		
	}

	/*using namespace std::chrono_literals;
	std::this_thread::sleep_for(5000ms);*/

	return 0;
}

/*
			Neuvoja:
 - derivaatan laskentaan pienempi h
 - newtonin iteraatiossa voisi tarkistaa onko nolla sijasta
	tulos < FLOAT_TOLERANCE jotta ollaa lahempana juurta.
 - varaudu asettamalla max iteraatiomaara jos nollakohtaa ei loydy
 - 
 - 
*/



/*			Tehtavananto
Palautustiedosto: submissions/t2/test_integration.cpp, submissions/t2/vastaukset.md, + screenshotit

Etsi funktion f(x) = x^3 - 1 juuri Newtonin menetelmalla, kun x0=0.5.
Etsi yhtalon f(x) = cos(x)-x^3 = 0 ratkaisu Newtonin menetelmalla, kun x0=0.5.

Etsi funktion f(x) = (x^4 + 11x^3 + 8x^2 + 20*x - 10) / 1000 minimi. Milla x:n arvolla se saadaan.

Muokkaa testisovellus sellaiseksi, etta se tulostaa oikean vastausksen konsoliin ja lisaksi piirtaa
ratkaistavan funktion ruudulle. Tallenna kukin funktio png-tiedostoon ja luo markdown syntaksin tiedosto
submissions/t2/vastaukset.md, jossa tulostetaan natisti (Kukin funktio oman otsikon alle) tehtavien funktiot
tekstina, niiden juuret ja linkki screensottiin.

Pisteytys: 1 p/funktio+visualisointi+oikea vastaus.
*/