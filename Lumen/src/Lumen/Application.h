#pragma once

#include "Core.h"

namespace Lumen {

	class LUMEN_API Application
	{
	public:
		Application();
		virtual ~Application(); // this will be subclasses by the sandbox Application

		void Run();
	};

	// To be defined in class
	Application* CreateApplication();
}


