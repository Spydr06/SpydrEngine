#pragma once

#include "Spydr/Renderer/VertexArray.h"

namespace Spydr
{
#define vvoid virtual void
#define ov override
#define cov const ov
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		vvoid Bind() cov;
		vvoid Unbind() cov;

		vvoid AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) ov;
		vvoid SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) ov;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

		uint32_t m_RendererID;
	};
#undef vvoid
#undef ov
#undef cov
}