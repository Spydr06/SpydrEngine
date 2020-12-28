#pragma once

#include "Spydr/Renderer/Shader.h"

namespace Spydr
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t m_RendererID;
	};
}