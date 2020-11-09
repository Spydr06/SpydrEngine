#include <Spydr.h>
#include <stdio.h>

class Sandbox : public Spydr::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Spydr::Application* Spydr::CreateApplication()
{
	return new Sandbox();
}