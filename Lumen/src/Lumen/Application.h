#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Lumen/Events/ApplicationEvents.h"

#include "Window.h"
#include "LayerStack.h"

namespace Lumen {

	class LUMEN_API Application
	{
	public:
		Application();
		virtual ~Application(); // this will be subclasses by the sandbox Application

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window; // unqiue ptr since it's unique for this class
		bool m_Running = true;
		LayerStack m_LayerStack;
	};


	// To be defined in class
	Application* CreateApplication();
}


