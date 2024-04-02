#pragma once

#include "../../Shaders/Shader.h"

#include <unordered_map>
#include <string>
#include <memory>

using std::vector;
using std::unordered_map;
using std::unique_ptr;

namespace Cannis {
	class ShaderManager {
	public:
		ShaderManager();

		// @brief Create a new shader with those given and save it
		// @param p_shaderName Name of the shader that will be used to retrieve it
		// @param p_vertexName Name of the vertex shader to compile
		// @param p_fragmentNme Name of the fragment shader to compile
		void addShader(const string& shaderName, const string& p_vertexName, const string& p_fragmentName);

		// @brief Add an existing shader
		// @param p_shaderName Name of the shader that will be used to retrieve it
		// @param p_newShader reference to the shader that will be saved
		void addShader(const string& p_shaderName, const Shader& p_newShader);

		// @brief Activates the given shader
		// @param p_shaderName Name of the shader that will be used
		void useShader(const string& p_shaderName) const;

		// @brief Set a uniform bool value to a shader
		// @param p_shaderName Name of the shader that will be used
		// @param p_valueName Name of the bool uniform inside the shader
		// @param p_value Value that will be assigned to the uniform
		void setBool(const string& p_shaderName, const string& p_valueName, const bool p_value) const;

		// @brief Destroys all shaders and resources used
		void clean();

	private:
		// @brief Decided to use a hash table so that it is 
		unordered_map<string,std::unique_ptr<Shader>> shaders;
	};

}
