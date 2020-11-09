#pragma once

#ifdef SP_PLATFORM_WINDOWS 

extern Spydr::Application* Spydr::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Spydr::CreateApplication();
	app->Run();
	delete app;
}

#endif
