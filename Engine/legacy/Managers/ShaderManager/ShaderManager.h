#pragma once

#include "../../Shaders/Shader.h"
#include "ShaderSlot/ShaderSlot.h"

#include <unordered_map>
#include <string>
#include <memory>

using std::vector;
using std::unordered_map;
using std::shared_ptr;

using Cannis::Shader;

namespace Cannis {
	class ShaderManager {
	public:
		ShaderManager();

		// @brief Create a new shader with a vertex and fragment shader files
		// @param p_shaderSlot Slot of the shader that will be used to retrieve it
		// @param p_vertexName Name of the vertex shader to compile
		// @param p_fragmentNme Name of the fragment shader to compile
		void addShader(const ShaderSlot::ShaderSlot p_shaderSlot, const string& p_vertexName, const string& p_fragmentName);

		// @brief Create a new shader with a vertex, fragment and geometry shader files
		// @param p_shaderSlot Slot of the shader that will be used to retrieve it
		// @param p_vertexName Name of the vertex shader to compile
		// @param p_fragmentNme Name of the fragment shader to compile
		// @param p_geometryShader Name of the geometry shader to compile
		void addShader(const ShaderSlot::ShaderSlot p_shaderSlot, const string& p_vertexName, const string& p_fragmentName, const string& p_geometryShader);

		// @brief Add an existing shader
		// @param p_shaderName Name of the shader that will be used to retrieve it
		// @param p_newShader reference to the shader that will be saved
		void addShader(const ShaderSlot::ShaderSlot p_shaderSlot, const Shader& p_newShader);

		const shared_ptr<Shader> getShader(const ShaderSlot::ShaderSlot p_shaderSlot) const;

		// @brief Activates a shader
		// @param p_shaderSlot Slot of the shader that will be used
		void useShader(const ShaderSlot::ShaderSlot p_shaderSlot) const;

		// @brief Set a uniform bool value to a shader
		// @param p_shaderSlot Slot of the shader that will be used
		// @param p_valueName Name of the bool uniform inside the shader
		// @param p_value Value that will be assigned to the uniform
		void setBool(const ShaderSlot::ShaderSlot p_shaderSlot, const string& p_valueName, const bool p_value) const;

		// @brief Set a uniform int value to a shader
		// @param p_shaderSlot Slot of the shader that will be used
		// @param p_valueName Name of the uniform inside the shader
		// @param p_value Value that will be assigned to the uniform
		void setInt(const ShaderSlot::ShaderSlot p_shaderSlot, const string& p_valueName, int p_value) const;
		
		// @brief Set a uniform float value to a shader
		// @param p_shaderSlot Slot of the shader that will be used
		// @param p_valueName Name of the uniform inside the shader
		// @param p_value Value that will be assigned to the uniform
		void setFloat(const ShaderSlot::ShaderSlot p_shaderSlot, const string& p_valueName, float p_value) const;
		
		// @brief Set a uniform Vector3 (3 floats) value to a shader
		// @param p_shaderSlot Slot of the shader that will be used
		// @param p_valueName Name of the uniform inside the shader
		// @param p_value Value that will be assigned to the uniform
		void setVec3(const ShaderSlot::ShaderSlot p_shaderSlot, const string& p_valueName, const glm::vec3& p_value) const;
		
		// @brief Set a uniform Vector3 (3 floats) value to a shader
		// @param p_shaderSlot Slot of the shader that will be used
		// @param p_valueName Name of the uniform inside the shader
		// @param p_x X value that will be assigned to the uniform's x component
		// @param p_y Y value that will be assigned to the uniform's y component
		// @param p_z Z value that will be assigned to the uniform's z component
		void setVec3(const ShaderSlot::ShaderSlot p_shaderSlot, const string& p_valueName, float p_x, float p_y, float p_z) const;
		
		// @brief Set a uniform Matrix3x3 (floats) value to a shader
		// @param p_shaderSlot Slot of the shader that will be used
		// @param p_valueName Name of the uniform inside the shader
		// @param p_value Value that will be assigned to the uniform
		void setMatrix3(const ShaderSlot::ShaderSlot p_shaderSlot, const string& p_valueName, glm::mat3& p_value) const;
		
		// @brief Set a uniform Matrix4x4 (floats) value to a shader
		// @param p_shaderSlot Slot of the shader that will be used
		// @param p_valueName Name of the uniform inside the shader
		// @param p_value Value that will be assigned to the uniform
		void setMatrix4(const ShaderSlot::ShaderSlot p_shaderSlot, const string& p_valueName, glm::mat4& p_value) const;

		// @brief Destroys all shaders and resources used
		void clean();

		// @brief 
		// @param p_newShader 
		void ChangeShader(ShaderSlot::ShaderSlot p_newShader);

		// @brief 
		ShaderSlot::ShaderSlot getCurrentShader();

	private:
		// @brief A faster hash map to get any shader, as an enum is used to retrieve the shader
		unordered_map<ShaderSlot::ShaderSlot, shared_ptr<Shader>> m_shaders;

		ShaderSlot::ShaderSlot m_currentShader;
	};
}