#include "sppch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Spydr {
	Ref<Texture2D> Texture2D::Create(const std::string& path) 
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			SP_CORE_ASSERT(false, "RenderAPI::None is currently not supported");
			break;
		case RenderAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(path);
		}

		SP_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			SP_CORE_ASSERT(false, "RenderAPI::None is currently not supported");
			break;
		case RenderAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(width, height);
		}

		SP_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}
}