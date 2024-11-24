#pragma once

#include "ccpch.h"
#include "Renderer/Buffer/VertexBuffer/VertexBuffer.h"

namespace Cannis {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(std::vector<Vertex>& p_vertices, size_t p_size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void UnBind() const override;

		const BufferLayout& GetLayout() const override;
		void SetLayout(const BufferLayout& p_bufferLayout) override;

	private:
		uint32_t m_ID;
		BufferLayout m_layout;
	};
}