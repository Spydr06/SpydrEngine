#pragma once

#if defined(SP_PLATFORM_WINDOWS) || defined (SP_PLATFORM_LINUX) 

extern Spydr::Application* Spydr::CreateApplication();

int main(int argc, char** argv)
{
	Spydr::Log::Init();
	SP_CORE_WARN("Initialized Log!");
	SP_INFO("Initialized Log!");

	auto app = Spydr::CreateApplication();
	app->Run();
	delete app;
}

#endif
