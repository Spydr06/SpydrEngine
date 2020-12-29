#pragma once

#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Spydr/Layers/LayerStack.h"

#include "Spydr/Renderer/Shader.h"
#include "Spydr/Renderer/Buffer.h"
#include "Spydr/Renderer/VertexArray.h"
#include "Spydr/Renderer/Renderer.h"

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

		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::unique_ptr<Window> m_Window;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
	private:
		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();
}

