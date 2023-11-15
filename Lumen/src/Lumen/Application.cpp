#include "lmpch.h"
#include "Application.h"

#include "Lumen/Events/ApplicationEvents.h"
#include "Lumen/Log.h"

namespace Lumen {


	Application::Application() 
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);		
		if (e.IsInCategory(EventCategoryApplication))
		{
			LM_CLIENT_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			LM_CLIENT_TRACE(e);;
		}
		while (true);
	}
}