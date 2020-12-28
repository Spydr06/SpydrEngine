#include "sppch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Spydr
{
	Shader* Shader::Create(std::string vertexSrc, std::string fragmentSrc)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			SP_CORE_ASSERT(false, "RendererAPI::None is not supported.");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		SP_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}