#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using std::string;

class Shader
{
public:
	unsigned int ID; /**< The Shader's program ID used to */
/*
 *	@brief Compiles the vertex and fragment shader so that they can be linked into a program, which will be saved into an ID ready to use
 *	@param vertexPath the file directory of your vertex shader. It should end on .vert
 *	@param fragmentPath the file directory of your fragment shader. It should end on .frag
*/
	Shader(const char* vertexPath, const char* fragmentPath);
/* @brief Deletes the program using this Shader's ID */
	~Shader(); 

	void Use();

	void SetBool(const string& name, bool value) const;
	void SetInt(const string& name, int value) const;
	void SetFloat(const string& name, float value) const;

private:
	string* GetSourceCode(const char* filePath);
	unsigned int CreateShader(const char* shaderCode, GLenum type);
	void CreateProgram(unsigned int vertexShader, unsigned int fragmentShader);
};

