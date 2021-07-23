#pragma once

#include "Spydr/Layers/Layer.h"

namespace Spydr
{
	class SPYDR_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnImGuiRender();
		virtual void OnAttach();
		virtual void OnDetach();

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}