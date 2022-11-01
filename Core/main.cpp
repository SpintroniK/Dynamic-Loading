#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "DLLoader.h"
#include "IPlanet.h"

using namespace std;

#ifdef WIN32
static const std::string bespinLibPath = "Bespin.dll";
static const std::string tatooineLibPath = "Tatooine.dll";
#endif
#ifdef __linux__
static const std::string bespinLibPath = "./libBespin.so";
static const std::string tatooineLibPath = "./libTatooine.so";
#endif
#ifdef __APPLE__
static const std::string bespinLibPath = "./libBespin.dylib";
static const std::string tatooineLibPath = "./libTatooine.dylib";
#endif

int main()
{

	auto planets = std::vector<Planet>{};
	planets.reserve(5);

	auto dlloader0 = std::make_shared<dlloader::DLLoader<Planet>>(tatooineLibPath);
	auto dlloader1 = std::make_shared<dlloader::DLLoader<Planet>>(bespinLibPath);
	
	planets.emplace_back(dlloader0->DLGetInstance());
	planets.emplace_back(dlloader0->DLGetInstance());
	planets.emplace_back(dlloader1->DLGetInstance());
	planets.emplace_back(dlloader1->DLGetInstance());
	// planets.emplace_back(dlloader1.DLGetInstance());

	planets.push_back(planets.back());
	for(const auto& p : planets)
	{
		p.greet();
	}


	return 0;
}
