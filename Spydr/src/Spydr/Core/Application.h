#pragma once

#include "Window.h"
#include "Spydr/Events/Event.h"
#include "Spydr/Events/ApplicationEvent.h"
#include "Spydr/Layers/LayerStack.h"

#include "Spydr/Core/Timestep.h"

#include "Spydr/ImGui/ImGuiLayer.h"

namespace Spydr
{
	class SPYDR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		std::unique_ptr<Window> m_Window;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();
}

