#include "VertexBuffer.h"

#include "../Renderer.h"

VertexBuffer::VertexBuffer(const void* p_data, unsigned int p_size) {
	glGenBuffers(1, &m_rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	glBufferData(GL_ARRAY_BUFFER, p_size, p_data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(m_rendererID);
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData() {
	std::lock_guard<std::mutex> lock(m);

	//Change buffer data
}
