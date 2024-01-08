#include "lmpch.h"
#include "Application.h"

#include "Lumen/Log.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "Lumen/Renderer/Renderer.h"
//#include "Lumen/Renderer/OrthographicCamera.h"
#include "Input.h"

namespace Lumen {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		LM_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float4, "a_Color"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);
		m_SquareVA.reset(VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		vertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			});
		m_SquareVA->AddVertexBuffer(vertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1);
			}	
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout (location = 0) out vec4 a_Color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				a_Color = vec4(v_Position * 0.5 + 0.5, 1.0);
				a_Color = v_Color;
			}	
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));


	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		LM_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}


	void Application::Run()
	{
		Renderer::Init();

		while (m_Running)
		{
			Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			Renderer::Clear();

			// Camera position
			// In order to move the camera back, travel on the positive Z axis, and vice versa.
			glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);

			// Camera Direction
			// Point the camera towards the scene's origin, (0, 0, 0);
			glm::vec3 m_CameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // Look at the scene's origin

			// Subtracting the scene we want to look at from the camera position, we can find the direction
			glm::vec3 m_CameraDirection = glm::normalize(m_CameraPosition - m_CameraTarget); // Actually points in the reverse direction of what it's looking at, so we'll have to inverse it

			// Create the right axis that represents the positive x-axis
			// A little trick is to create an up vector in world space, (0.0f, 1.0f, 0.0f) and use the camera direction to perform a cross product 
			glm::vec3 m_VectorUp = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 m_CameraRight = glm::normalize((glm::cross(m_VectorUp, m_CameraDirection)));

			// m_Camera = X, m_CameraDirection = Z, time to find Y
			// Perform the cross product of X and Y
			glm::vec3 m_CameraUp = glm::cross(m_CameraUp, m_CameraDirection);

			const float radius = 0.0f;
			float m_CameraX = sin(glfwGetTime() * radius);
			float m_CameraZ = cos(glfwGetTime() * radius);
			glm::mat4 view = glm::lookAt(glm::vec3(m_CameraX, 0.0, m_CameraZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));


			glm::mat4 m_ProjectionMatrix;
			glm::mat4 m_ViewMatrix;
			glm::mat4 m_ViewProjectionMatrix; // Uses 64 bytes more, but can be used to cache M*V*P instead of calculating every time


			glm::vec3 m_Position;
			float m_Rotation = 0.0f; // Keep track of rotations
	 
			Renderer::BeginScene();

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		exit(0);
		return true;
	}
}