#pragma once

#include "ccpch.h"

namespace Cannis {
	enum ShaderType {
		Vertex,
		Fragment,
		Geometry
	};

	class Shader {
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static std::unique_ptr<Shader> Create(const std::string& p_vertexSource, const std::string& p_fragmentSource);
	};
}