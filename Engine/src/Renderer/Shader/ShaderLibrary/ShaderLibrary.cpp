#include "ccpch.h"
#include "ShaderLibrary.h"

#include <filesystem>

namespace Cannis {
	ShaderLibrary::ShaderLibrary() {
		CC_CORE_INFO(std::filesystem::current_path().string());
		m_registeredShaders.insert({ ShaderImplementation::Model, Shader::Create("../Engine/assets/Shaders/FlatColor/flatColor.vert", "../Engine/assets/Shaders/FlatColor/flatColor.frag") });
		m_registeredShaders.insert({ ShaderImplementation::Blinn_Phong, Shader::Create("../Engine/assets/Shaders/Blinn_Phong/blinn_phong.vert", "../Engine/assets/Shaders/Blinn_Phong/blinn_phong.frag") });
		m_registeredShaders.insert({ ShaderImplementation::PBR, Shader::Create("../Engine/assets/Shaders/PBR/pbr.vert", "../Engine/assets/Shaders/PBR/pbr.frag") });
	}

	std::shared_ptr<Shader>& ShaderLibrary::GetRegisteredShader(const ShaderImplementation p_shaderImpl) {
		return m_registeredShaders[p_shaderImpl];
	}

	void ShaderLibrary::BindShader(const ShaderImplementation p_shaderImpl) {
		m_registeredShaders[p_shaderImpl]->Bind();
	}

	void ShaderLibrary::UnbindShader(const ShaderImplementation p_shaderImpl) {
		m_registeredShaders[p_shaderImpl]->UnBind();
	}

	uint32_t ShaderLibrary::GetShaderID(const ShaderImplementation p_shaderImpl) {
		return m_registeredShaders[p_shaderImpl]->GetID();
	}
}