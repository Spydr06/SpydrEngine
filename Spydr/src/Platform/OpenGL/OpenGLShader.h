#pragma once

#include "Spydr/Renderer/Shader.h"

namespace Spydr
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const override;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& values) const override;
	private:
		uint32_t m_RendererID;
	};
}