#include "ccpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/RendererAPI/OpenGLRendererAPI.h"

namespace Cannis {
	std::unique_ptr<RendererAPI> RenderCommand::s_rendererAPI = std::make_unique<OpenGLRendererAPI>();
}