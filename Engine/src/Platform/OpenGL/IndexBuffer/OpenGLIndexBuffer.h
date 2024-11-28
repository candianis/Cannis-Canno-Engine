#pragma once

#include "ccpch.h"
#include "Renderer/Buffer/IndexBuffer/IndexBuffer.h"

namespace Cannis {
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(std::shared_ptr<std::vector<uint32_t>>& p_indices, size_t p_size);
		virtual ~OpenGLIndexBuffer();

		void Bind() const override;
		void UnBind() const override;
		inline size_t GetCount() const override { return m_count; }

	private:
		uint32_t m_ID;
		size_t m_count;
	};
}