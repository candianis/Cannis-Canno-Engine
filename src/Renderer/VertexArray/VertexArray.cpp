#include "VertexArray.h"

#include "../Renderer.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_rendererID);
	glBindVertexArray(m_rendererID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(m_rendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& p_vb, const VertexBufferLayout& p_layout) {
	Bind();
	p_vb.Bind();
	const auto& elements = p_layout.GetElements();

	unsigned int offset = 0;
	for (size_t i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, p_layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const {
	glBindVertexArray(m_rendererID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}
