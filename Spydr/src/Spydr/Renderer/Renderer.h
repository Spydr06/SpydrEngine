#pragma once

#include "RenderCommand.h"

namespace Spydr {
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void SubmitVertexData(const std::shared_ptr<VertexArray>& vertexData);

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	};
}