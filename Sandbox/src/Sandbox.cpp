#include <Lumen.h>

class ExampleLayer : public Lumen::Layer
{
public:
	ExampleLayer() 
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		m_VertexArray.reset(Lumen::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};
		std::shared_ptr<Lumen::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Lumen::VertexBuffer::Create(vertices, sizeof(vertices)));
		Lumen::BufferLayout layout = {
			{ Lumen::ShaderDataType::Float3, "a_Position"},
			{ Lumen::ShaderDataType::Float4, "a_Color"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Lumen::IndexBuffer> indexBuffer;
		indexBuffer.reset(Lumen::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);
		m_SquareVA.reset(Lumen::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		vertexBuffer.reset(Lumen::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		vertexBuffer->SetLayout({
			{ Lumen::ShaderDataType::Float3, "a_Position" },
			});
		m_SquareVA->AddVertexBuffer(vertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Lumen::IndexBuffer> squareIB;
		squareIB.reset(Lumen::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1);
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

		m_Shader.reset(new Lumen::Shader(vertexSrc, fragmentSrc));
	}

	void OnUpdate() override
	{
		Lumen::Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Lumen::Renderer::Clear();

		m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });
		m_Camera.SetRotation(45.0f);

		Lumen::Renderer::BeginScene(m_Camera);

		Lumen::Renderer::Submit(m_Shader, m_VertexArray);

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

