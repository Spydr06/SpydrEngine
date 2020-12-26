#pragma once

#include "Spydr/Core.h"
#include "Spydr/Events/Event.h"

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
		vvoid OnUpdate() {}
		vvoid OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
#undef vvoid
}