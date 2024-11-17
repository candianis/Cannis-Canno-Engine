#include "ccpch.h"
#include "BufferLayout.h"

namespace Cannis {
	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& p_elements) : m_elements(p_elements), m_stride(0) {
		CalculateOffsetAndStride();
	}

	void BufferLayout::CalculateOffsetAndStride() {
		uint32_t offset = 0;
		for (BufferElement& element : m_elements) {
			element.offset = offset;
			offset += element.size;
			m_stride += element.size;
		}
	}
}