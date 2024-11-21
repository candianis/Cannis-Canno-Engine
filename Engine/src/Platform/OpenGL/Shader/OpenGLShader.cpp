#include "ccpch.h"

#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Cannis {
	GLenum GetCorrectShaderEnum(ShaderType p_shaderType) {
		switch (p_shaderType) {
		case ShaderType::Vertex:
			return GL_VERTEX_SHADER;

		case ShaderType::Fragment:
			return GL_FRAGMENT_SHADER;

		case ShaderType::Geometry:
			return GL_GEOMETRY_SHADER;
		}
	}

	OpenGLShader::OpenGLShader(const std::string& p_vertexSource, const std::string& p_fragmentSource) {
		std::string vertCode(GetSourceCode(p_vertexSource.c_str()));
		std::string fragCode(GetSourceCode(p_fragmentSource.c_str()));

		unsigned int vertexShader = CreateShader(vertCode.c_str(), ShaderType::Vertex);
		unsigned int fragmentShader = CreateShader(fragCode.c_str(), ShaderType::Fragment);

		CreateProgram(vertexShader, fragmentShader);

		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_ID);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_ID);
	}

	void OpenGLShader::UnBind() const {
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniform(const std::string& p_name, const int p_value) {
		glUniform1i(glGetUniformLocation(m_ID, p_name.c_str()), p_value);
	}

	// ----- Float ----- //
	void OpenGLShader::UploadUniform(const std::string& p_name, const float p_value) {
		glUniform1f(glGetUniformLocation(m_ID, p_name.c_str()), p_value);
	}

	// ----- Vector2 ----- //
	void OpenGLShader::UploadUniform(const std::string& p_name, const glm::vec2& p_vector) {
		glUniform2f(glGetUniformLocation(m_ID, p_name.c_str()), p_vector.x, p_vector.y);
	}

	void OpenGLShader::UploadUniform(const std::string& p_name, const float p_x, const float p_y) {
		glUniform2f(glGetUniformLocation(m_ID, p_name.c_str()), p_x, p_y);
	}

	// ----- Vector3 ----- //
	void OpenGLShader::UploadUniform(const std::string& p_name, const glm::vec3& p_vector) {
		glUniform3f(glGetUniformLocation(m_ID, p_name.c_str()), p_vector.x, p_vector.y, p_vector.z);
	}

	void OpenGLShader::UploadUniform(const std::string& p_name, const float p_x, const float p_y, const float p_z) {
		glUniform3f(glGetUniformLocation(m_ID, p_name.c_str()), p_x, p_y, p_z);
	}

	// ----- Vector4 ----- //
	void OpenGLShader::UploadUniform(const std::string& p_name, const glm::vec4& p_vector) {
		glUniform4f(glGetUniformLocation(m_ID, p_name.c_str()), p_vector.x, p_vector.y, p_vector.z, p_vector.w);
	}

	void OpenGLShader::UploadUniform(const std::string& p_name, const float p_x, const float p_y, const float p_z, const float p_w) {
		glUniform4f(glGetUniformLocation(m_ID, p_name.c_str()), p_x, p_y, p_z, p_w);
	}

	// ----- Matrices ----- //
	void OpenGLShader::UploadUniform(const std::string& p_name, const glm::mat3& p_matrix) {
		glUniformMatrix3fv(glGetUniformLocation(m_ID, p_name.c_str()), 1, GL_FALSE, glm::value_ptr(p_matrix));
	}

	void OpenGLShader::UploadUniform(const std::string& p_name, const glm::mat4& p_matrix) {
		glUniformMatrix4fv(glGetUniformLocation(m_ID, p_name.c_str()), 1, GL_FALSE, glm::value_ptr(p_matrix));
	}

	string OpenGLShader::GetSourceCode(const char* p_filePath) {
		string code;
		std::ifstream shaderFile;

		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			shaderFile.open(p_filePath, std::ios::in);

			if (!shaderFile.is_open()) {
				std::cout << "ERR: Failed to open the file: " << p_filePath << std::endl;
			}

			if (!shaderFile.good()) {
				std::cout << "ERR: An error was found while trying to read the file: " << p_filePath << std::endl;
			}

			std::stringstream shaderStream;
			// read file's buffer contents into streams
			shaderStream << shaderFile.rdbuf();

			shaderFile.close();

			code = shaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		return code;
	}

	unsigned int OpenGLShader::CreateShader(const char* p_shaderCode, ShaderType p_type) {
		unsigned int shader;

		GLenum shaderType = GetCorrectShaderEnum(p_type);

		shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &p_shaderCode, NULL);
		glCompileShader(shader);

		//Check for shader compilation errors
		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success) {
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::string shaderTypeName = p_type == ShaderType::Vertex ? "VERTEX" : "FRAGMENT";
			CC_CORE_ERROR("ERROR::SHADER::{0}::COMPILATION_FAILED", shaderTypeName);
			CC_CORE_ERROR("{0}", infoLog);
		}

		return shader;
	}

	void OpenGLShader::CreateProgram(unsigned int p_vertexShader, unsigned int p_fragmentShader) {
		m_ID = glCreateProgram();
		glAttachShader(m_ID, p_vertexShader);
		glAttachShader(m_ID, p_fragmentShader);
		glLinkProgram(m_ID);

		int success;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);

		if (!success) {
			char test[512];
			glGetProgramInfoLog(m_ID, 512, NULL, test);
			CC_CORE_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED");
			CC_CORE_ERROR("{0}", test);
		}

		//Clean the shaders as they are no longer needed
		glDetachShader(m_ID, p_vertexShader);
		glDeleteShader(p_vertexShader);

		glDetachShader(m_ID, p_fragmentShader);
		glDeleteShader(p_fragmentShader);
	}
}