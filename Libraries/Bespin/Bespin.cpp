#include "Bespin.h"

#include <iostream>

#if defined(__linux__) || defined(__APPLE__)
extern "C"
{
	Bespin *allocator()
	{
        std::cout << "Allocate Bespin" << std::endl;
		return new Bespin();
	}

	void deleter(Bespin *ptr)
	{
        std::cout << "Delete Bespin" << std::endl;
		delete ptr;
	}
}
#endif

#ifdef WIN32
extern "C"
{
	__declspec (dllexport) Bespin *allocator()
	{
		return new Bespin();
	}

	__declspec (dllexport) void deleter(Bespin *ptr)
	{
		delete ptr;
	}
}
#endif

void Bespin::greet() const
{
	std::cout << "Greetings from Bespin !" << std::endl;
}
