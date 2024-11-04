#pragma once

#include "ccpch.h"

namespace Cannis {
	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static std::shared_ptr<VertexBuffer> Create(float* p_vertices, size_t p_size);
	};
}