#pragma once

#include "Spydr/Layer.h"

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
		float m_Time = 0.0f;
	};
}