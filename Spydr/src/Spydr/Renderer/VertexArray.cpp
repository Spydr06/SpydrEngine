#include "sppch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Spydr
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:		
			SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return false;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		}

		SP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}