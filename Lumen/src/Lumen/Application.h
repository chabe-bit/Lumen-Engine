#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Lumen/Events/ApplicationEvents.h"

#include "Window.h"
#include "LayerStack.h"

#include "Lumen/Core/Timestep.h"
#include "Lumen/imgui_folder/ImGuiLayer.h"

#include "Lumen/Renderer/Shader.h"
#include "Lumen/Renderer/Buffer.h"
#include "Lumen/Renderer/OrthographicCamera.h"
#include "Lumen/Renderer/VertexArray.h"

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
	private:

		std::unique_ptr<Window> m_Window; // unqiue ptr since it's unique for this class
		bool m_Running = true;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f; 

	private:
		static Application* s_Instance;
	};


	// To be defined in class
	Application* CreateApplication();
}


