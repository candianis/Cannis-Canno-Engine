#pragma once

#include "ccpch.h"
#include <glad/glad.h>

namespace Cannis {
	enum class ShaderDataType {
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType p_type) {
		switch (p_type) {
			case ShaderDataType::Float:	 return  4;
			case ShaderDataType::Float2: return  8;
			case ShaderDataType::Float3: return 12;
			case ShaderDataType::Float4: return 16;

			case ShaderDataType::Mat3:   return  9 * 4;
			case ShaderDataType::Mat4:   return 16 * 4;

			case ShaderDataType::Int:    return  4;
			case ShaderDataType::Int2:   return  8;
			case ShaderDataType::Int3:   return 12;
			case ShaderDataType::Int4:   return 16;

			case ShaderDataType::Bool:   return  1;
		}

		CC_CORE_ASSERT(false, "Unkown data type");
		return 0;
	}

	static GLenum ShaderDataTypeToGLEnum(ShaderDataType p_shaderData) {
		switch (p_shaderData) {
			case ShaderDataType::Float:	
			case ShaderDataType::Float2: 
			case ShaderDataType::Float3: 
			case ShaderDataType::Float4: 
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
				return GL_FLOAT;


			case ShaderDataType::Int: 
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
				return GL_INT;

			case ShaderDataType::Bool:
				return GL_BOOL;
		}

		CC_CORE_ASSERT(false, "Unkown data type");
		return 0;
	}
}