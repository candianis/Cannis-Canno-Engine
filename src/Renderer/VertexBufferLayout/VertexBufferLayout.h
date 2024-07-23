#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cassert>
#include <vector>

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	VertexBufferElement(unsigned int p_type, unsigned int p_count, bool p_normalized) : type(p_type), count(p_count), normalized(p_normalized) {}
	static unsigned int GetSizeOfType(unsigned int p_type) {
		switch (p_type) {
			case GL_FLOAT:
				return 4;

			case GL_UNSIGNED_INT:
				return 4;

			case GL_UNSIGNED_BYTE:
				return 1;
		}
		assert(false && "Failed to get type's size");
		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_stride;

public:
	VertexBufferLayout() : m_stride(0) {}

	template<typename T>
	void Push(int count) {
		static_assert(false);
	}

	template<>
	void Push<float>(int count) {
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(int count) {
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(int count) {
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_elements; }
	inline unsigned int GetStride() const { return m_stride; }
};