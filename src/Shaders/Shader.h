#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void Use();

	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;

private:
	std::string* GetSourceCode(const char* filePath);
	unsigned int CreateShader(const char* shaderCode, GLenum type);
	void CreateProgram(unsigned int vertexShader, unsigned int fragmentShader);
};

