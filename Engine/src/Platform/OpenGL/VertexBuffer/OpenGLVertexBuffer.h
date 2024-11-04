#pragma once

#include "ccpch.h"
#include "Renderer/VertexBuffer/VertexBuffer.h"

namespace Cannis {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* p_vertices, size_t p_size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void UnBind() const override;

	private:
		uint32_t m_ID;
	};
}