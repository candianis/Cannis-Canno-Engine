#pragma once

#include "ccpch.h"

#include "Renderer/Shader/Shader.h"

namespace Cannis {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& p_vertexSource, const std::string& p_fragmentSource);
		virtual ~OpenGLShader();

		void Bind() const override;
		void UnBind() const override;
		inline uint32_t GetID() const { return m_ID; }

		void UploadUniform(const std::string& p_name, const glm::vec3& p_vector) override;
		void UploadUniform(const std::string& p_name, const glm::mat4& p_matrix) override;

	private:
		// @brief Transform the text file of any shader into a string
		// @param p_filePath Complete file path of the shader
		// @returns Get the shader code (.vert/.frag) as a string
		string GetSourceCode(const char* p_filePath);

		// @brief Creates a vertex or fragment shader
		// @param p_shaderCode Pointer to the shader's file as a string
		// @param p_type Type of the shader such as GL_VERTEX/FRAGMENT/GEOMETRY_SHADER
		// @returns The newly created shader's ID
		unsigned int CreateShader(const char* p_shaderCode, ShaderType p_type);

		// @brief Compiles and links a new shader with the given .vert and .frag files
		// @param p_vertexShader ID of the vertex shader to attach to the shader
		// @param p_fragmentShader ID of the fragment shader to attach to the shader
		void CreateProgram(unsigned int p_vertexShader, unsigned int p_fragmentShader);

		uint32_t m_ID;
	};
}