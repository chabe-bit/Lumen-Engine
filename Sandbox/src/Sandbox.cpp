#include <Lumen.h>

class ExampleLayer : public Lumen::Layer
{
public:
	ExampleLayer() 
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		LM_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Lumen::Event& event) override
	{
		LM_CLIENT_TRACE("{0}", event);
	}


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

