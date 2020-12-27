#pragma once

namespace Spydr
{
#define vvoid virtual void
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		vvoid Bind() const = 0;
		vvoid Unbind() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		vvoid Bind() const = 0;
		vvoid Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* vertices, uint32_t size);
	};
#undef vvoid
}