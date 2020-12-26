#pragma once

#include "Spydr/Layers/Layer.h"
#include "Spydr/Events/MouseEvent.h"
#include "Spydr/Events/KeyEvent.h"
#include "Spydr/Events/ApplicationEvent.h"

namespace Spydr
{
	class SPYDR_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnUpdate();
		void OnEvent(Event& event);
		void OnAttach();
		void OnDetach();
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		bool OnKeyTypedEvent(KeyTypedEvent& event);
		bool OnWindowResizeEvent(WindowResizeEvent& event);

		float m_Time = 0.0f;
	};
}