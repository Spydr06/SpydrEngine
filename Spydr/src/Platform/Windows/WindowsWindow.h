#pragma once

#include "Spydr/Window.h"
#include "Spydr/Renderer/GraphicsContext.h"

#include "GLFW/glfw3.h"

namespace Spydr
{
#define uint unsigned int
#define vvoid virtual void
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline uint GetWidth() const override { return m_Data.Width; }
		inline uint GetHeight() const override { return m_Data.Height; }

		//Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline vvoid* GetNativeWindow() const { return m_Window; };
	private:
		vvoid Init(const WindowProps& props);
		vvoid Shutdown();
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			uint Width;
			uint Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
#undef uint
#undef vvoid
}