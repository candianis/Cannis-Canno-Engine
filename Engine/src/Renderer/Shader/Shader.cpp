#include "ccpch.h"

#include "Shader.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/Shader/OpenGLShader.h"

#include <glad/glad.h>

 
namespace Cannis {
	std::shared_ptr<Shader> Shader::Create(const std::string& p_vertexSource, const std::string& p_fragmentSource) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				CC_CORE_ASSERT(false, "No API was chosen");
				return nullptr;
				break;

			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(p_vertexSource, p_fragmentSource);
				break;
		}

		CC_CORE_ASSERT(false, "Uknown Rendering API");
		return nullptr;
	}
}