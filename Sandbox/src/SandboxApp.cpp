#include <Spydr.h>
#include <stdio.h>

class ExampleLayer : public Spydr::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnUpdate() override
	{
		SP_INFO("ExampleLayer::Update");
	}

	void OnEvent(Spydr::Event& event) override
	{
		SP_TRACE("{0}", event);
	}
};

class Sandbox : public Spydr::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Spydr::Application* Spydr::CreateApplication()
{
	return new Sandbox();
}