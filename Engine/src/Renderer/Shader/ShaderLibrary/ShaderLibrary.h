#pragma once

#include "ccpch.h"
#include "Renderer/Shader/Shader.h"
#include "Renderer/Shader/ShaderImplementation.h"

namespace Cannis {
	class ShaderLibrary {
	public:
		ShaderLibrary();
		~ShaderLibrary() = default;

		std::shared_ptr<Shader>& GetRegisteredShader(const ShaderImplementation p_shaderImpl);
		void BindShader(const ShaderImplementation p_shaderImpl);
		void UnbindShader(const ShaderImplementation p_shaderImpl);
		uint32_t GetShaderID(const ShaderImplementation p_shaderImpl);

	private:
		std::unordered_map<ShaderImplementation, std::shared_ptr<Shader>> m_registeredShaders;
	};
}