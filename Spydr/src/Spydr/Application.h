#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Spydr
{
	class SPYDR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in client.
	Application* CreateApplication();
}

