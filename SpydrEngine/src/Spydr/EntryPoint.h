#pragma once

#ifdef SP_PLATFORM_WINDOWS 

extern Spydr::Application* Spydr::CreateApplication();

int main(int argc, char** argv)
{
	Spydr::Log::Init();
	SP_CORE_INFO("Initialized Log!");
	SP_INFO("Initialized Log!");

	auto app = Spydr::CreateApplication();
	app->Run();
	delete app;
}

#endif
