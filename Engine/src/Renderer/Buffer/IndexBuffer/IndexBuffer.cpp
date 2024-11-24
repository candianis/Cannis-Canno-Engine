#include "ccpch.h"

#include "IndexBuffer.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/IndexBuffer/OpenGLIndexBuffer.h"

namespace Cannis {
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(std::vector<uint32_t>& p_indices, size_t p_count) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			CC_CORE_ASSERT(false, "No API was chosen");
			return nullptr;
			break;

		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(p_indices, p_count);
			break;
		}

		CC_CORE_ASSERT(false, "Uknown Rendering API");
		return nullptr;
	}
}