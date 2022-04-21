#pragma once

#include "Spydr/Core/Core.h"
#include "Spydr/Events/Event.h"
#include "Spydr/Core/Timestep.h"

namespace Spydr
{
#define vvoid virtual void

	class SPYDR_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		vvoid OnAttach() {}
		vvoid OnDetach() {}
		vvoid OnUpdate(Timestep ts) {}
		vvoid OnEvent(Event& event) {}
		vvoid OnImGuiRender() {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
#undef vvoid
}