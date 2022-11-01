#pragma once

#include <iostream>
#include <dlfcn.h>

#include "IPlanet.h"
#include "IDLLoader.h"

namespace dlloader
{
	template <class T>
	class DLLoader : public std::enable_shared_from_this<DLLoader<T>>, public IDLLoader<T>
	{

	private:

		void			*_handle;
		std::string		_pathToLib;
		std::string		_allocClassSymbol;
		std::string		_deleteClassSymbol;

	public:

		DLLoader(std::string const &pathToLib,
			std::string const &allocClassSymbol = "allocator",
			std::string const &deleteClassSymbol = "deleter") :
			_handle(nullptr), _pathToLib(pathToLib),
			_allocClassSymbol(allocClassSymbol), _deleteClassSymbol(deleteClassSymbol)
		{
			std::cout << "Open dl loader " << _pathToLib << std::endl;
			if (!(_handle = dlopen(_pathToLib.c_str(), RTLD_NOW | RTLD_LAZY))) 
			{
				std::cerr << dlerror() << std::endl;
			}
		}

		~DLLoader()
		{
			std::cout << "Close dl loader " << _pathToLib << std::endl;
			DLCloseLib();
		}

		void DLOpenLib() override
		{
			if (!(_handle = dlopen(_pathToLib.c_str(), RTLD_NOW | RTLD_LAZY))) 
			{
				std::cerr << dlerror() << std::endl;
			}
		}

		T DLGetInstance() override
		{
			using allocClass = IPlanet *(*)();
			using deleteClass = void (*)(IPlanet *);


			const auto allocFunc = reinterpret_cast<allocClass>(dlsym(_handle, _allocClassSymbol.c_str()));
			const auto deleteFunc = reinterpret_cast<deleteClass>(dlsym(_handle, _deleteClassSymbol.c_str()));

			if (!allocFunc || !deleteFunc) 
			{
				DLCloseLib();
				std::cerr << dlerror() << std::endl;
			}

			return T{allocFunc(), [deleteFunc](auto* p) { deleteFunc(p); }, this->shared_from_this()};
		}

		void DLCloseLib() override
		{
			if (dlclose(_handle) != 0) 
			{
				std::cerr << dlerror() << std::endl;
			}
		}

	};
}
