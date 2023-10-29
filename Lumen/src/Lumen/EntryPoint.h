#pragma once

#ifdef LM_PLATFORM_WINDOWS

extern Lumen::Application* Lumen::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Lumen::CreateApplication();
	app->Run();
	delete app;
}

#endif