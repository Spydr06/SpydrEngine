#include "sppch.h"
#include "Application.h"

#include "Spydr/Events/ApplicationEvent.h"
#include "Spydr/Log.h"

namespace Spydr
{

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1920, 1080);
		SP_TRACE(e);

		while (true);
	}
}