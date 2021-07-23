#pragma once

namespace Spydr
{
#define vvoid virtual void
	class GraphicsContext
	{
	public:
		vvoid Init() = 0;
		vvoid SwapBuffers() = 0;
	};
#undef vvoid
}