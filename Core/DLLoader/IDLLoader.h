#pragma once

#include <functional>
#include <memory>
#include <string>
#include <utility>

namespace dlloader
{

	/*
	** Interface for Dynamic Library Loading (DLLoader)
	** API for Unix and Windows. Handling of open, close, validity-check.
	*/
	template <class T>
	class IDLLoader
	{

	public:

		virtual ~IDLLoader() = default;

		/*
		**
		*/
		virtual void DLOpenLib() = 0;

		/*
		** Return a shared pointer on an instance of class loaded through
		** a dynamic library.
		*/
		virtual T DLGetInstance() = 0;

		/*
		** Correctly delete the instance of the "dynamically loaded" class.
		*/
		virtual void DLCloseLib() = 0;

	};
}
