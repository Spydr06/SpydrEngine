#pragma once

#include <string>

namespace Spydr
{
	class Shader
	{
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(std::string vertexSrc, std::string fragmentSrc);
	private:
		uint32_t m_RendererID;
	};
}