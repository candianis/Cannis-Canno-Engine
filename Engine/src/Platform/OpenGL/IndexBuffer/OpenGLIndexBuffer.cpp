#include "ccpch.h"

#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace Cannis {
	OpenGLIndexBuffer::OpenGLIndexBuffer(std::vector<uint32_t>& p_indices, size_t p_count) : m_count(p_count) {
		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		// TODO: atioxx.dll error here for models with more than one mesh
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_count * sizeof(uint32_t), p_indices.data(), GL_STATIC_DRAW);
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