#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Lumen {

	class LUMEN_API Application
	{
	public:
		Application();
		virtual ~Application(); // this will be subclasses by the sandbox Application

		void Run();
	private:
		std::unique_ptr<Window> m_Window; // unqiue ptr since it's unique for this class
		bool m_Running = true;
	};


	// To be defined in class
	Application* CreateApplication();
}


