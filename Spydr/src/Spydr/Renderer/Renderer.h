#pragma once

#include "RenderCommand.h"
#include "Cameras/OrthographicCamera.h"
#include "Shader.h"

namespace Spydr {
	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResized(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void SubmitVertexData(const std::shared_ptr<VertexArray>& vertexData, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}