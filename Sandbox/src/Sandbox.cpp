#include <Lumen.h>

#include "Platforms/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public Lumen::Layer
{
public:
	ExampleLayer() 
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Lumen::VertexArray::Create());

		float vertices[4 * 7] = {
			// positions        // colors
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // bottom left
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // bottom right
			 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
			-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f  // top left
		};
		std::shared_ptr<Lumen::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Lumen::VertexBuffer::Create(vertices, sizeof(vertices)));
		Lumen::BufferLayout layout = {
			{ Lumen::ShaderDataType::Float3, "a_Position"},
			{ Lumen::ShaderDataType::Float4, "a_Color"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = {
			0, 1, 2, // First triangle (bottom left, bottom right, top right)
			2, 3, 0  // Second triangle (top right, top left, bottom left)
		};
		std::shared_ptr<Lumen::IndexBuffer> indexBuffer;
		indexBuffer.reset(Lumen::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1);
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

		m_Shader.reset(Lumen::Shader::Create(vertexSrc, fragmentSrc));
	}

	void OnUpdate(Lumen::Timestep ts) override
	{

		if (Lumen::Input::IsKeyPressed(LM_KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed * ts;
		else if (Lumen::Input::IsKeyPressed(LM_KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed * ts;
		else if (Lumen::Input::IsKeyPressed(LM_KEY_UP))
			m_CameraPosition.y += m_CameraSpeed * ts;
		else if (Lumen::Input::IsKeyPressed(LM_KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed * ts;


		Lumen::Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Lumen::Renderer::Clear();

		m_Camera.SetPosition(m_CameraPosition);

		Lumen::Renderer::BeginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Lumen::OpenGLShader>(m_Shader)->Bind();
		std::dynamic_pointer_cast<Lumen::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Lumen::Renderer::Submit(m_Shader, m_VertexArray, transform);
			}
		}



		Lumen::Renderer::EndScene();
	}


	void OnEvent(Lumen::Event& event) override
	{

	}


private:
	std::shared_ptr<Lumen::Shader> m_Shader;
	std::shared_ptr<Lumen::VertexArray> m_VertexArray;

	std::shared_ptr<Lumen::Shader> m_BlueShader;
	std::shared_ptr<Lumen::VertexArray> m_SquareVA;
	 
	Lumen::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 0.1f;

	glm::vec3 m_SquareColor = { 0.2f, 0.4f, 0.4 };
};

class Sandbox : public Lumen::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Lumen::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Lumen::Application* Lumen::CreateApplication()
{
	return new Sandbox();
}

