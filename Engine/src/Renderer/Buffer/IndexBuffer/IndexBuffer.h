#pragma once

#include "ccpch.h"

namespace Cannis {
	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual size_t GetCount() const = 0;

		static std::shared_ptr<IndexBuffer> Create(std::vector<uint32_t>& p_indices, size_t p_count);
	};
}