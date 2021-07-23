#pragma once

#include "Spydr/Renderer/Buffer.h"

namespace Spydr
{
#define vvoid virtual void
#define cov const override
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		vvoid Bind() cov;
		vvoid Unbind() cov;

		vvoid SetLayout(const BufferLayout& layout) const override { m_Layout = layout; };
		virtual const BufferLayout& GetLayout() cov { return m_Layout; };
	private:
		uint32_t m_RendererID;
		BufferLayout& m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer();

		vvoid Bind() cov;
		vvoid Unbind() cov;

		virtual uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
#undef vvoid
#undef cov
}