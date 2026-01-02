#include <mikroplot/window.h>

#include <stdio.h>
#include <iostream>

#include <cmath>

#include <thread>
#include <fstream>

#include "FileWritingFunctions.h"

// all functions
auto pow2(float x)					//1
{
	return x * x;
}
auto pow3(float x)					//2
{
	return x * x * x;
}

auto sine(float x)					//3
{
	return sinf(x);
}

auto cosine(float x)				//4
{
	return cosf(x);
}

auto cubicPolonomial(float x)		//5
{
	return 2 * pow3(x) + 5 * pow2(x) + 6 * x + 2;
}

auto exponentialBaseE(float x)			//6
{
	return expf(x);
}

auto naturalLOG(float x)			//7
{
	return logf(x);
}

auto squareroot(float x)			//8
{
	return sqrtf(x);
}

auto prodSinCos(float x)			//9
{
	return sinf(x) * cosf(x);
}

auto weightedProdSinCos(float x)	//10
{
	return 2.3f * sinf(x) * 1.2f * cosf(x);
}

auto weightedSumSinCos(float x)		//11
{
	return 2.3f * sinf(x) + 1.2f * cosf(x);
}

auto tangent(float x)				//12
{
	return tanf(x);
}

auto cubeRoot(float x)					//13
{
	return cbrtf(x);
}

auto binryExponential(float x)		//14
{
	return exp2f(x);
}

auto gamma(float x)					//15
{
	return tgammaf(x);
}

auto commonLOG(float x)				//16
{
	return log10f(x);
}

auto exponentialMinusOne(float x)	//17
{
	return expm1f(x);
}

auto quarticPolynomial(float x)		//18
{
	return (x * x * x * x) - pow2(4 * x) + 4;
}

auto gaussinjakauma(float x)		//19
{
	return exp(pow2(-x));
}

auto scaledExponentialPolynomial(float x)		//20
{
	return (pow2(x)*exp(-x));
}

auto rationalFunction(float x)		//21
{
	return (1/(1+pow2(x)));
}

auto quinticPolynomial(float x)		//22
{
	return (x * x * x * x * x) - 5 * pow3(x) + 4 * x;
}

/*
auto xxx(float x)
{
	return xxx(x);
}
*/



int main()
{
	int function_index = 0;

	//create filehandler and set up stuff
	FileHandler filehandler(__FILE__, "vastaukset.md");
	filehandler.writeLineInFile("# Vastaukset\n");
	filehandler.writeLineInFile("# Eetu Horttanainen\n");

	std::string filelocation = filehandler.getFilelocation();
	
	mikroplot::Window window(800, 800, "Fuktioiden_Kuvaajien_Piirtaminen");

	//Linux kaantaja vaatii jostain syysta etta funktiolista alustettaisiin lambdoilla
	std::vector<std::function<float(float)>> functions = {

		[](float x) {return pow2(x); },
		[](float x) {return pow3(x); } ,
		[](float x) {return sine(x); },
		[](float x) {return cosine(x); },
		[](float x) {return cubicPolonomial(x); },
		[](float x) {return exponentialBaseE(x); },
		[](float x) {return naturalLOG(x); },
		[](float x) {return squareroot(x); },
		[](float x) {return commonLOG(x); },
		[](float x) {return prodSinCos(x); },
		[](float x) {return weightedProdSinCos(x); },
		[](float x) {return weightedSumSinCos(x); },
		[](float x) {return tangent(x); },				//////////////////////
		[](float x) {return cubeRoot(x); },
		[](float x) {return gamma(x); },
		[](float x) {return binryExponential(x); },
		[](float x) {return exponentialMinusOne(x); },
		[](float x) {return quarticPolynomial(x); },
		[](float x) {return scaledExponentialPolynomial(x); },
		[](float x) {return rationalFunction(x); },
		[](float x) {return quinticPolynomial(x); },
		[](float x) {return gaussinjakauma(x); },			//22
	};

	std::vector <std::string> functionNames = {
		"square","cube",
		"sine","cosine",
		"cubic polynomial","exponential baseE","natural logarithm",
		"squareroot","common logarithm","product of sin cos",
		"weighted product of sin & cos","weighted sum of sin & cos","tangent","cube root", "gamma",
		"binry exponential","exponential minus one","quartic polynomial",
		"scaled exponential polynomial","rational function","quintic polynomial","gaussinjakauma",

		"funcname","funcname","funcname","funcname","funcname","funcname","funcname","funcname",
		"funcname","funcname","funcname","funcname","funcname","funcname","funcname","funcname",
		"funcname","funcname","funcname","funcname","funcname","funcname","funcname","funcname",
	};

	std::vector <std::string> functionSyntaxes = {
		"x^2","x^3",
		"sin(x)","cos(x)",
		"2 * x^3 + 5 * x^2 + 6 * x + 2","e^x","ln(x)",
		"sqrt(x)","log10(x)","sin(x) * cos(x)",
		"2.3f * sin(x) * 1.2f * cos(x)","2.3f * sin(x) + 1.2f * cos(x)","tan(x)","cbrt(x)","(x-1)!",
		"2^x","e^x-1","x^4 - (4 * x)^2 + 4",
		"(x^2*exp(-x))","1/(1+x^2)","x^5 - 5 * x^3 + 4 * x","exp(-x^2)",

		"funcname","funcname","funcname","funcname","funcname","funcname","funcname","funcname",
		"funcname","funcname","funcname","funcname","funcname","funcname","funcname","funcname",
		"funcname","funcname","funcname","funcname","funcname","funcname","funcname","funcname",
	};
	
	window.update();

	while (false == window.shouldClose())
	{
		window.setScreen(-10, 10, -10, 10);

		window.drawAxis();

		window.drawFunction(functions[function_index], 11, 4);

		window.update();

		//write into file
		std::string PNGfilename = std::to_string(function_index) + ".png";
		window.screenshot(filelocation+"\\"+PNGfilename);
		filehandler.writeLineInFile("Funktio Nimi: " + functionNames[function_index] + "\n\n");
		filehandler.writeLineInFile("Funktio: " + functionSyntaxes[function_index] + "\n\n");
		filehandler.writeLineInFile(
			"![](" + PNGfilename + " \"Funktio:" + std::to_string(function_index) + "\")"+ "\n\n"
		);

		function_index++;

		using namespace std::chrono_literals;
		std::this_thread::sleep_for(1300ms);

		if (function_index >= functions.size())
		{
			window.update();
			break;
		}

	}
	return 0;
}

/*			Tehtavananto
Palautustiedosto: submissions/t1/test_draw_functions.cpp,
submissions/t1/vastaukset.md ja screenshotit submissions/t1/xxx.png
Tee sovellus, joka piirtaa seuraavanlaisia funktioita ruudulle:

Polynomeja, kuten:

x*x
x*x
2xxx + 5xx + 6x + 2. sin(x)
cos(x)
e^x
ln(x)
sqrt(x)
sin(x)*cos(x)
2.3*sin(x)1.2cos(x)
2.3sin(x)+1.2cos(x)
x^x
jne (keksi itse loput funktiot ja kokeile! :)).


Piirra myos kyseisten funktioiden derivaattoja.
Muokkaa funktioiden "parametreja", lisaa animointeja ajan avulla ja testaile ja hahmottele
funktioiden kayttaytymista eri tilanteissa (testaa minimissaan 20 eri funktion toimintaa)
Muokkaa testisovellus sellaiseksi, etta se ottaa automaattisesti screenshotteja kustakin
funktion kuvaajasta. Kuvien palautus submissions/t1/xxx.png, missa xxx on juokseva numero.
Palauta repositoryyn cpp, markdown ja png:t, jossa upotettuna png screenshotit.

Pisteytys: 0.25 p/funktio.
*/