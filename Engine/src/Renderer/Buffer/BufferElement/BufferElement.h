#pragma once

#include "ccpch.h"
#include "Renderer/Shader/ShaderDataType.h"

namespace Cannis {
	struct BufferElement {
		std::string name;
		ShaderDataType type;
		uint32_t size;
		uint32_t offset;
		bool normalized;

		BufferElement(const std::string& p_name, ShaderDataType p_type, bool p_isNormalized = false) : name(p_name), type(p_type), size(ShaderDataTypeSize(p_type)), offset(0), normalized(p_isNormalized) {}

		uint32_t GetComponentCount() const {
			switch (type) {
				case ShaderDataType::Float:	 return 1;
				case ShaderDataType::Float2: return 2;
				case ShaderDataType::Float3: return 3;
				case ShaderDataType::Float4: return 4;

				case ShaderDataType::Mat3:   return  9;
				case ShaderDataType::Mat4:   return 16;

				case ShaderDataType::Int:    return 1;
				case ShaderDataType::Int2:   return 2;
				case ShaderDataType::Int3:   return 3;
				case ShaderDataType::Int4:   return 4;

				case ShaderDataType::Bool:   return  1;
			}

			CC_CORE_ASSERT(false, "Unkown data type");
			return 0;
		}
	};
}