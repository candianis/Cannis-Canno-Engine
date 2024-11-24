#pragma once

#include "ccpch.h"
#include <glm/glm.hpp>

namespace Cannis {
	enum ShaderType {
		VertexShader,
		FragmentShader,
		GeometryShader
	};

	class Shader {
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual uint32_t GetID() const = 0;

		virtual void UploadUniform(const std::string& p_name, const int p_value) = 0;
		
		virtual void UploadUniform(const std::string& p_name, const float p_value) = 0;
		virtual void UploadUniform(const std::string& p_name, const glm::vec2& p_vector) = 0;
		virtual void UploadUniform(const std::string& p_name, const float p_x, const float p_y) = 0;
		virtual void UploadUniform(const std::string& p_name, const glm::vec3& p_vector) = 0;
		virtual void UploadUniform(const std::string& p_name, const float p_x, const float p_y, const float p_z) = 0;
		virtual void UploadUniform(const std::string& p_name, const glm::vec4& p_vector) = 0;
		virtual void UploadUniform(const std::string& p_name, const float p_x, const float p_y, const float p_z, const float p_w) = 0;

		virtual void UploadUniform(const std::string& p_name, const glm::mat3& p_matrix) = 0;
		virtual void UploadUniform(const std::string& p_name, const glm::mat4& p_matrix) = 0;

		static std::shared_ptr<Shader> Create(const std::string& p_vertexSource, const std::string& p_fragmentSource);
	};
}