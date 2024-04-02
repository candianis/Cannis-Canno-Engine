#include "ShaderManager.h"

using Cannis::ShaderManager;

ShaderManager::ShaderManager() {
	
}

void ShaderManager::addShader(const string& shaderName, const string& p_vertexName, const string& p_fragmentName) {
	shaders.try_emplace(shaderName, std::make_unique<Shader>(p_vertexName.c_str(), p_fragmentName.c_str()));
}

void ShaderManager::addShader(const string& p_shaderName, const Shader& p_newShader) {
	
}

void ShaderManager::useShader(const string& p_shaderName) const {
	shaders.at(p_shaderName)->use();
}

void ShaderManager::setBool(const string& p_shaderName, const string& p_valueName, const bool p_value) const {
	glUniform1i(glGetUniformLocation(shaders.at(p_shaderName)->ID, p_valueName.c_str()), (int)p_value);
}

void ShaderManager::clean() {
	for (auto it = shaders.begin(); it != shaders.end(); ++it) {
		it->second->clean();
	}
}
