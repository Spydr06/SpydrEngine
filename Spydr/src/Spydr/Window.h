#pragma once

#include "sppch.h"

#include "Spydr/Core.h"
#include "Spydr/Events/Event.h"

namespace Spydr
{
#define vvoid virtual void
#define uint unsigned int
#define vuint virtual uint

	struct WindowProps
	{
		std::string Title;
		uint Width;
		uint Height;

		WindowProps(const std::string& title = "Spydr Engine", uint width = 1280, uint height = 720) : Title(title), Width(width), Height(height)
		{
		}
	};

	//Interface representing a desktop system Window (platform independant!)
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}
		vvoid OnUpdate() = 0;

		vuint GetWidth() const = 0;
		vuint GetHeight() const = 0;

		//Window attributes
		vvoid SetEventCallback(const EventCallbackFn& callback) = 0;
		vvoid SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		vvoid* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};

#undef vuint
#undef uint
#undef vvoid
}