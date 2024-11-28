#include "ccpch.h"

#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace Cannis {
	OpenGLVertexBuffer::OpenGLVertexBuffer(std::shared_ptr<std::vector<Vertex>>& p_vertices, size_t p_size) {
		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, p_size, p_vertices->data(), GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &m_ID);
	}

	void OpenGLVertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void OpenGLVertexBuffer::UnBind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	const BufferLayout& OpenGLVertexBuffer::GetLayout() const {
		return m_layout;
	}

	void OpenGLVertexBuffer::SetLayout(const BufferLayout& p_bufferLayout) {
		m_layout = p_bufferLayout;
	}
}