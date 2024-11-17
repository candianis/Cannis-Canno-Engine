#pragma once

#include "ccpch.h"

#include "Renderer/VertexArray/VertexArray.h"

namespace Cannis {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		void Bind() const override;
		void UnBind() const override;

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& p_vertexBuffer) override;
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& p_indexBuffer) override;

		inline const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_vertexBuffers; }
		inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_indexBuffer; }

	private:
		uint32_t m_ID;
		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
		std::shared_ptr<IndexBuffer> m_indexBuffer;
	};
}