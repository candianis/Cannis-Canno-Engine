#include "ShaderManager.h"

using Cannis::ShaderManager;

ShaderManager::ShaderManager() {
	m_currentShader = ShaderSlot::Model_Visualization;

	addShader(ShaderSlot::Model_Visualization, "model_visual.vert", "model_visual.frag");
	addShader(ShaderSlot::Phong, "basic_light.vert", "basic_light.frag");
	addShader(ShaderSlot::Blinn_Phong, "blinn_phong.vert", "blinn_phong.frag");
}

void ShaderManager::addShader(const ShaderSlot::ShaderSlot p_shaderSlot, const string& p_vertexName, const string& p_fragmentName) {
	m_shaders.try_emplace(p_shaderSlot, std::make_shared<Shader>(p_vertexName.c_str(), p_fragmentName.c_str()));
}

void ShaderManager::addShader(const ShaderSlot::ShaderSlot p_shaderSlot, const string& p_vertexName, const string& p_fragmentName, const string& p_geometryShader) {
	m_shaders.try_emplace(p_shaderSlot, std::make_shared<Shader>(p_vertexName.c_str(), p_fragmentName.c_str(), p_geometryShader.c_str()));
}


void ShaderManager::addShader(const ShaderSlot::ShaderSlot p_shaderSlot, const Shader& p_newShader) {
	m_shaders.try_emplace(p_shaderSlot, std::make_shared<Shader>(p_newShader));
}

const shared_ptr<Shader> ShaderManager::getShader(const ShaderSlot::ShaderSlot p_shaderSlot) const {
	return m_shaders.at(p_shaderSlot);
}

void ShaderManager::useShader(const ShaderSlot::ShaderSlot p_shaderSlot) const {
	m_shaders.at(p_shaderSlot)->use();
}

void ShaderManager::setBool(const ShaderSlot::ShaderSlot p_shaderName, const string& p_valueName, const bool p_value) const {
	glUniform1i(glGetUniformLocation(m_shaders.at(p_shaderName)->ID, p_valueName.c_str()), (int)p_value);
}

void ShaderManager::setInt(const ShaderSlot::ShaderSlot p_shaderSlot, const string& p_valueName, int p_value) const {
	glUniform1i(glGetUniformLocation(m_shaders.at(p_shaderSlot)->ID, p_valueName.c_str()), p_value);
}

void ShaderManager::setFloat(const ShaderSlot::ShaderSlot p_shaderSlot, const string& p_valueName, float p_value) const {
	glUniform1f(glGetUniformLocation(m_shaders.at(p_shaderSlot)->ID, p_valueName.c_str()), p_value);
}

void ShaderManager::setVec3(const ShaderSlot::ShaderSlot p_shaderSlot, const string& p_valueName, const glm::vec3& p_value) const {
	glUniform3f(glGetUniformLocation(m_shaders.at(p_shaderSlot)->ID, p_valueName.c_str()), p_value.x, p_value.y, p_value.z);
}

void ShaderManager::setVec3(const ShaderSlot::ShaderSlot p_shaderSlot, const string& p_valueName, float p_x, float p_y, float p_z) const {
	glUniform3f(glGetUniformLocation(m_shaders.at(p_shaderSlot)->ID, p_valueName.c_str()), p_x, p_y, p_z);
}

void ShaderManager::setMatrix3(const ShaderSlot::ShaderSlot p_shaderSlot, const string& p_valueName, glm::mat3& p_value) const {
	glUniformMatrix3fv(glGetUniformLocation(m_shaders.at(p_shaderSlot)->ID, p_valueName.c_str()), 1, GL_FALSE, glm::value_ptr(p_value));
}

void ShaderManager::setMatrix4(const ShaderSlot::ShaderSlot p_shaderSlot, const string& p_valueName, glm::mat4& p_value) const {
	glUniformMatrix4fv(glGetUniformLocation(m_shaders.at(p_shaderSlot)->ID, p_valueName.c_str()), 1, GL_FALSE, glm::value_ptr(p_value));
}

void ShaderManager::clean() {
	for (auto it = m_shaders.begin(); it != m_shaders.end(); ++it) {
		it->second->clean();
	}
}
