#include "IndexBuffer.h"

#include "../Renderer.h"

#include <cassert>

IndexBuffer::IndexBuffer(const unsigned int* p_data, unsigned int p_count) : m_count(p_count) {
	assert(sizeof(unsigned int) != sizeof(GLuint) && "Uint and OpenGL's are different\n");

	glGenBuffers(1, &m_rendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_count * sizeof(unsigned int), p_data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &m_rendererID);
}

void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

void IndexBuffer::Unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
