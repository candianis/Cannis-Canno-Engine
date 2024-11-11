#include "ccpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Cannis {
	OpenGLVertexArray::OpenGLVertexArray(float* p_vertices, size_t p_size, size_t p_stride) : m_size(p_size) {
		glGenVertexArrays(1, &m_ID);
		glBindVertexArray(m_ID);

		glBufferData(GL_ARRAY_BUFFER, p_size, p_vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, p_stride, nullptr);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_ID);
	}

	void OpenGLVertexArray::Bind() {
		glBindVertexArray(m_ID);
	}

	void OpenGLVertexArray::UnBind() {
		glBindVertexArray(0);
	}

	size_t OpenGLVertexArray::GetSize() const {
		return m_size;
	}
}
