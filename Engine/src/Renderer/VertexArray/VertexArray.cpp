#include "ccpch.h"

#include "VertexArray.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/VertexArray/OpenGLVertexArray.h"

namespace Cannis {
	std::unique_ptr<VertexArray> VertexArray::Create(float* p_vertices, size_t p_size, size_t p_stride) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::None:
				CC_CORE_ASSERT(false, "No API was chosen");
				return nullptr;
				break;

			case RendererAPI::OpenGL:
				return std::make_unique<OpenGLVertexArray>(p_vertices, p_size, p_stride);
				break;
		}

		CC_CORE_ASSERT(false, "Uknown Rendering API");
		return nullptr;
	}
}