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

namespace Cannis {
	class Shader {
		public:
			unsigned int ID; /**< The Shader's program ID used to */
			
		 	// @brief Compiles the vertex and fragment shader so that they can be linked into a program, which will be saved into an ID ready to use
			// @param p_vertexPath the file name of your vertex shader. It should end on .vert and be inside Shaders/Vertex
			// @param p_fragmentPath the file name of your fragment shader. It should end on .frag and be inside Shaders/Fragment
			Shader(const char* p_vertexName, const char* p_fragmentName);

			// @brief Compiles the vertex, fragment and geometry shader so that they can be linked into a program, which will be saved into an ID ready to use
			// @param p_vertexPath the file name of your vertex shader. It should end on .vert and be inside Shaders/Vertex
			// @param p_fragmentPath the file name of your fragment shader. It should end on .frag and be inside Shaders/Fragment
			// @param p_geometryName the file name of the geometry shader. It should end on .geom and be inside Shaders/Geometry
			Shader(const char* p_vertexName, const char* p_fragmentName, const char* p_geometryName);

			// @brief Initialize a Shader with an existing one
			// @param p_shader Shader to copy
			Shader(const Shader& p_shader);

			// @brief Deletes the program using this Shader's ID
			~Shader();

			// @brief Asks OpenGL to use this shader
			void Bind() const;

			void Unbind() const;

			//Set uniforms

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

			// @brief Deletes the shader program
			void clean();

		private:
			// @brief Transform the text file of any shader into a string
			// @param p_filePath Complete file path of the shader
			// @returns Get the shader code (.vert/.frag) as a string
			string getSourceCode(const char* p_filePath);

			// @brief Creates a vertex or fragment shader
			// @param p_shaderCode Pointer to the shader's file as a string
			// @param p_type Type of the shader such as GL_VERTEX/FRAGMENT/GEOMETRY_SHADER
			// @returns The newly created shader's ID
			unsigned int createShader(const char* p_shaderCode, GLenum p_type);

			// @brief Compiles and links a new shader with the given .vert and .frag files
			// @param p_vertexShader ID of the vertex shader to attach to the shader
			// @param p_fragmentShader ID of the fragment shader to attach to the shader
			void createProgram(unsigned int p_vertexShader, unsigned int p_fragmentShader);
			
			// @brief Compiles and links a new shader with the given .vert, .frag and .geom files
			// @param p_vertexShader ID of the vertex shader to attach to the shader
			// @param p_fragmentShader ID of the fragment shader to attach to the shader
			// @param p_geometryShader ID of the geometry shader to attach to the shader
			// @note An error will occur if the geometry shader ID does not exist
			void createProgram(unsigned int p_vertexShader, unsigned int p_fragmentShader, unsigned int p_geometryShader);
	};
}
