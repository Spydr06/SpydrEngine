#pragma once

#include "Spydr/Core.h"
#include "Layer.h"

#include <vector>

namespace Spydr
{
#define vec(x) std::vector<x>
	class SPYDR_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		vec(Layer*)::iterator begin() { return m_Layers.begin(); }
		vec(Layer*)::iterator end() { return m_Layers.end(); }
	private:
		vec(Layer*) m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
#undef vec
}