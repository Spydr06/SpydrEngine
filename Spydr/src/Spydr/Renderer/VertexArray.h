#pragma once

#include <memory>
#include "Buffer.h"

namespace Spydr
{
#define vvoid virtual void
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		vvoid Bind() const = 0;
		vvoid Unbind() const = 0;

		vvoid AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) = 0;
		vvoid SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
#undef vvoid
}