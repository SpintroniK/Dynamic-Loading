#include "Tatooine.h"

#include <iostream>

#if defined(__linux__) || defined(__APPLE__)
extern "C"
{
	Tatooine *allocator()
	{
        std::cout << "Allocate Tatooine" << std::endl;
		return new Tatooine();
	}

	void deleter(Tatooine *ptr)
	{
        std::cout << "Delete Tatooine" << std::endl;
		delete ptr;
	}
}
#endif

#ifdef WIN32
extern "C"
{
	__declspec (dllexport) Tatooine *allocator()
	{
		return new Tatooine();
	}

	__declspec (dllexport) void deleter(Tatooine *ptr)
	{
		delete ptr;
	}
}
#endif

void Tatooine::greet() const
{
	std::cout << "Greetings from Tatooine !" << std::endl;
}
