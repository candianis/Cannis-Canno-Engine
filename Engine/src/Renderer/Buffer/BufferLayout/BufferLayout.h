#pragma once

#include "ccpch.h"
#include "Renderer/Buffer/BufferElement/BufferElement.h"

namespace Cannis {
	class BufferLayout {
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& p_elements);

		~BufferLayout() = default;

		inline const std::vector<BufferElement>& GetElements() const { return m_elements; }
		inline const uint32_t GetStride() const { return m_stride; }

		// @Notes This function needs to be lowercased so that it can be used in for each loops
		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.cbegin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_elements.cend(); }

	private:
		std::vector<BufferElement> m_elements;
		uint32_t m_stride;

		void CalculateOffsetAndStride();
	};
}