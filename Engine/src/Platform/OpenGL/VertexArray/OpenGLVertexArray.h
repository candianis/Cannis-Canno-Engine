#pragma once

#include "ccpch.h"

#include "Renderer/VertexArray/VertexArray.h"

namespace Cannis {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray(float* p_vertices, size_t p_size, size_t p_stride);
		virtual ~OpenGLVertexArray();

		void Bind() override;
		void UnBind() override;
		size_t GetSize() const;

	private:
		uint32_t m_ID;
		size_t m_size;
	};
}