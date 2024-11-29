#include "ccpch.h"

#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace Cannis {
	OpenGLIndexBuffer::OpenGLIndexBuffer(std::shared_ptr<std::vector<uint32_t>>& p_indices, size_t p_count) : m_count(p_count) {
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_count * sizeof(uint32_t), 0, GL_STATIC_DRAW);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, p_count * sizeof(uint32_t), &p_indices->front());
		CC_CORE_ERROR(glGetError());
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &m_ID);
	}

	void OpenGLIndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

	void OpenGLIndexBuffer::UnBind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}
}