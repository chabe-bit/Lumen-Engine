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

		if (Lumen::Input::IsKeyPressed(LM_KEY_TAB))
			LM_CLIENT_INFO("Tab key is pressed! (poll)");
	}

	void OnEvent(Lumen::Event& event) override
	{

		if (event.GetEventType() == Lumen::EventType::KeyPressed)
		{
			Lumen::KeyPressedEvent& e = (Lumen::KeyPressedEvent&)event;
			if (e.GetKeyCode() == LM_KEY_TAB)
				LM_CLIENT_TRACE("Tab key is pressed! (event)");
			LM_CLIENT_TRACE("{0}", (char)e.GetKeyCode());
		}

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

