#pragma once

#ifdef LM_PLATFORM_WINDOWS

// This can be done on the application but it's better for it to be taken care of on the system side

extern Lumen::Application* Lumen::CreateApplication();

int main(int argc, char** argv)
{
	Lumen::Log::Init();
	LM_CORE_WARN("Initialized Log!");
	int a = 5;
	LM_CLIENT_INFO("Var={0}", a);

	auto app = Lumen::CreateApplication();
	app->Run();
	delete app;
}

#endif