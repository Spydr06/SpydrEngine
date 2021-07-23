#include "sppch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Spydr
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
		case RenderAPI::API::None:
			SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}

		SP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}