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
			return std::make_shared<OpenGLTexture2D>(path);
		}

		SP_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}
}