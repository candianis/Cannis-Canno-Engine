#pragma once

#include "ccpch.h"
#include "Renderer/Shader/Shader.h"

namespace Cannis {
	struct ShaderComponent {
		ShaderComponent() = default;
		ShaderComponent(const std::string& p_vertexSource, const std::string& p_fragmentSource) : shader(Shader::Create(p_vertexSource, p_fragmentSource)) {}

		std::shared_ptr<Shader> shader;
	};
}