#include "sppch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Spydr
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
		case RenderAPI::API::None:
			SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return false;
		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}

		SP_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}