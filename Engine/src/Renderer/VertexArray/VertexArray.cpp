#include "ccpch.h"

#include "VertexArray.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/VertexArray/OpenGLVertexArray.h"

namespace Cannis {
	std::shared_ptr<VertexArray> VertexArray::Create() {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				CC_CORE_ASSERT(false, "No API was chosen");
				return nullptr;
				break;

			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLVertexArray>();
				break;
		}

		CC_CORE_ASSERT(false, "Uknown Rendering API");
		return nullptr;
	}
}