#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string* vertCode = GetSourceCode(vertexPath);
	std::string* fragCode = GetSourceCode(fragmentPath);

	unsigned int vertexShader = CreateShader(vertCode->c_str(), GL_VERTEX_SHADER);
	unsigned int fragmentShader = CreateShader(fragCode->c_str(), GL_FRAGMENT_SHADER);

	CreateProgram(vertexShader, fragmentShader);

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Return the memory we asked for when getting the sourceCode
	delete(vertCode);
	delete(fragCode);
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

std::string* Shader::GetSourceCode(const char* filePath) {
	std::string* code = new std::string();
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		shaderFile.open(filePath, std::ios::in);

		if (!shaderFile.is_open()) {
			std::cout << "ERR: Failed to open the file: " << filePath << std::endl;
		}

		if (!shaderFile.good()) {
			std::cout << "ERR: An error was found while trying to read the file: " << filePath << std::endl;
		}

		std::stringstream shaderStream;
		// read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();

		shaderFile.close();

		*code = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	return code;
}

unsigned int Shader::CreateShader(const char* shaderCode, GLenum type) {
	unsigned int shader;
	int success;
	char infoLog[512];

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);

	//Check for shader compilation errors
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::string errorType = type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";
		std::cout << "ERROR::SHADER::" + errorType + "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}

void Shader::CreateProgram(unsigned int vertexShader, unsigned int fragmentShader) {
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	int success;
	char infoLog[512];

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//Clean the shaders as they are no longer needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}