#pragma once

#include "Spydr/Renderer/RenderAPI.h"

namespace Spydr
{
	class OpenGLRenderAPI : public RenderAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}