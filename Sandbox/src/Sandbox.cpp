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

		float vertices[] = {
			// positions        // colors
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // top left
		};
		std::shared_ptr<Lumen::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Lumen::VertexBuffer::Create(vertices, sizeof(vertices)));
		Lumen::BufferLayout layout = {
			{ Lumen::ShaderDataType::Float3, "a_Position"},
			{ Lumen::ShaderDataType::Float2, "a_TexCoord"},
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

		std::string vertexTextureSrc = R"(
			#version 330 core
			
			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1);
			}	
		)";

		std::string fragmentTextureSrc = R"(
			#version 330 core
			
			layout (location = 0) out vec4 a_Color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				a_Color = texture(u_Texture, v_TexCoord);
			}	
		)";

		m_TextureShader.reset(Lumen::Shader::Create(vertexTextureSrc, fragmentTextureSrc));
	
		m_Texture = (Lumen::Texture2D::Create("assets/textures/something_new.jpg"));
	
		std::dynamic_pointer_cast<Lumen::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Lumen::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
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

		m_Texture->Bind();
		Lumen::Renderer::Submit(m_TextureShader, m_VertexArray, glm::scale(glm::mat4(1.0), glm::vec3(1.5f)));


		Lumen::Renderer::EndScene();
	}


	void OnEvent(Lumen::Event& event) override
	{

	}


private:
	Lumen::Ref<Lumen::Shader> m_Shader, m_TextureShader;
	Lumen::Ref<Lumen::VertexArray> m_VertexArray;

	Lumen::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 0.1f;

	Lumen::Ref<Lumen::Texture2D> m_Texture;

	glm::vec3 m_SquareColor = { 0.2f, 0.4f, 0.4 };
};

class Sandbox : public Lumen::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Lumen::Application* Lumen::CreateApplication()
{
	return new Sandbox();
}

