#include "Shader.h"

using Cannis::Shader;

Shader::Shader(const char* p_vertexName, const char* p_fragmentName) {
	string vertexPath = "./src/Shaders/Vertex/";
	vertexPath += p_vertexName;
	string vertCode(getSourceCode(vertexPath.c_str()));
	string fragmentPath = "./src/Shaders/Fragment/";
	fragmentPath += p_fragmentName;
	string fragCode(getSourceCode(fragmentPath.c_str()));

	unsigned int vertexShader = createShader(vertCode.c_str(), GL_VERTEX_SHADER);
	unsigned int fragmentShader = createShader(fragCode.c_str(), GL_FRAGMENT_SHADER);

	createProgram(vertexShader, fragmentShader);

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::Shader(const char* p_vertexName, const char* p_fragmentName, const char* p_geometryName) {
	string vertexPath = "./src/Shaders/Vertex/";
	vertexPath += p_vertexName;
	string vertCode(getSourceCode(vertexPath.c_str()));

	string fragmentPath = "./src/Shaders/Fragment/";
	fragmentPath += p_fragmentName;
	string fragCode(getSourceCode(fragmentPath.c_str()));

	string geometryPath = "./src/Shaders/Geometry/";
	geometryPath += p_geometryName;
	string geometryCode(getSourceCode(geometryPath.c_str()));

	unsigned int vertexShader = createShader(vertCode.c_str(), GL_VERTEX_SHADER);
	unsigned int fragmentShader = createShader(fragCode.c_str(), GL_FRAGMENT_SHADER);
	unsigned int geometryShader = createShader(geometryCode.c_str(), GL_GEOMETRY_SHADER);

	createProgram(vertexShader, fragmentShader, geometryShader);

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(geometryShader);
}

Shader::Shader(const Shader& p_shader) {
	this->ID = p_shader.ID;
}

Shader::~Shader() {
	glDeleteProgram(ID);
}

void Shader::use() const {
	glUseProgram(ID);
}

void Shader::setBool(const string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const string& name, const glm::vec3& value) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void Shader::setVec3(const string& name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setMatrix3(const string& name, glm::mat3& values) const {
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(values));
}

void Shader::setMatrix4(const string& name, glm::mat4& values) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(values));
}

void Shader::clean()
{
	glDeleteProgram(ID);
}

string Shader::getSourceCode(const char* p_filePath) {
	if (p_filePath == nullptr) {
		std::cout << "ERR::PathIsNull" << std::endl;
		return "";
	}

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

unsigned int Shader::createShader(const char* shaderCode, GLenum type) {
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
		string errorType = type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";
		std::cout << "ERROR::SHADER::" + errorType + "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}

void Shader::createProgram(unsigned int p_vertexShader, unsigned int p_fragmentShader) {
	ID = glCreateProgram();
	glAttachShader(ID, p_vertexShader);
	glAttachShader(ID, p_fragmentShader);
	glLinkProgram(ID);

	int success;
	char infoLog[512];

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//Clean the shaders as they are no longer needed
	glDeleteShader(p_vertexShader);
	glDeleteShader(p_fragmentShader);
}

void Shader::createProgram(unsigned int p_vertexShader, unsigned int p_fragmentShader, unsigned int p_geometryShader) {
	ID = glCreateProgram();
	glAttachShader(ID, p_vertexShader);
	glAttachShader(ID, p_fragmentShader);
	glAttachShader(ID, p_geometryShader);
	glLinkProgram(ID);

	int success;
	char infoLog[512];

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//Clean the shaders as they are no longer needed
	glDeleteShader(p_vertexShader);
	glDeleteShader(p_fragmentShader);
	glDeleteShader(p_geometryShader);
}