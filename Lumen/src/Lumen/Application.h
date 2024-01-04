#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Lumen/Events/ApplicationEvents.h"

#include "Window.h"
#include "LayerStack.h"

#include "Lumen/Renderer/Shader.h"
#include "Lumen/Renderer/Buffer.h"

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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window; // unqiue ptr since it's unique for this class
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

	private:
		static Application* s_Instance;
	};


	// To be defined in class
	Application* CreateApplication();
}


