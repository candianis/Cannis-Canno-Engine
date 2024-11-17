#include "ccpch.h"

#include "VertexBuffer.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/VertexBuffer/OpenGLVertexBuffer.h"

namespace Cannis {
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* p_vertices, size_t p_size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::None:
				CC_CORE_ASSERT(false, "No API was chosen");
				return nullptr;
				break;
		
			case RendererAPI::OpenGL:
				return std::make_shared<OpenGLVertexBuffer>(p_vertices, p_size);
				break;
		}

		CC_CORE_ASSERT(false, "Uknown Rendering API");
		return nullptr;
	}
}