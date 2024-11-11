#pragma once

#include "ccpch.h"

namespace Cannis {
	class VertexArray {
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		static std::unique_ptr<VertexArray> Create(float* p_vertices, size_t p_size, size_t p_stride);
	};
}