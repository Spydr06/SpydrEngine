#include "sppch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Spydr
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
		case RenderAPI::API::None: 
			SP_CORE_ASSERT(false, "RendererAPI::None is not supported.");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		SP_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
		case RenderAPI::API::None:
			SP_CORE_ASSERT(false, "RendererAPI::None is not supported.");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, size);
		}

		SP_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}