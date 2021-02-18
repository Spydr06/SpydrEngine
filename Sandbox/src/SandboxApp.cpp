#include <Spydr.h>
#include <Spydr/Core/EntryPoint.h>

#include "GameLayer.h"

class Sandbox : public Spydr::Application
{
public:
	Sandbox()
	{
		PushLayer(new GameLayer());
	}

	~Sandbox()
	{
	}
};

Spydr::Application* Spydr::CreateApplication()
{
	return new Sandbox();
}