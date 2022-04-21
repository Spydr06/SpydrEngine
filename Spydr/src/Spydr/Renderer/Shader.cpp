#include "sppch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Spydr
{
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI()) {
		case RenderAPI::API::None:
			SP_CORE_ASSERT(false, "RendererAPI::None is not supported.");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		SP_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& filepath) {
		switch (Renderer::GetAPI()) {
		case RenderAPI::API::None:
			SP_CORE_ASSERT(false, "RendererAPI::None is not supported.");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		}

		SP_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		SP_CORE_ASSERT(!Exists(name), "Shader already exists");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		Add(shader->GetName(), shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		SP_CORE_ASSERT(Exists(name), "Shader does not exist");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const 
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}