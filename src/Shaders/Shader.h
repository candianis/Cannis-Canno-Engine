#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using std::string;

/*@brief */
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

	/**/
	void use();

	/**/
	void setBool(const string& name, bool value) const;
	/**/
	void setInt(const string& name, int value) const;
	/**/
	void setFloat(const string& name, float value) const;
	/**/
	void setVec3(const string& name, const glm::vec3& value) const;
	/**/
	void setVec3(const string& name, float x, float y, float z) const;
	/**/
	void setMatrix3(const string& name, glm::mat3& values) const;
	/**/
	void setMatrix4(const string& name, glm::mat4& values) const;

private:
	/*@brief */
	string* GetSourceCode(const char* filePath);
	/*@brief */
	unsigned int CreateShader(const char* shaderCode, GLenum type);
	/*@brief */
	void CreateProgram(unsigned int vertexShader, unsigned int fragmentShader);
};

