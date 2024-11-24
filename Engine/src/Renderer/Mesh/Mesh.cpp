#include "ccpch.h"
#include "Mesh.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/Mesh/OpenGLMesh.h"

namespace Cannis {
	std::shared_ptr<Mesh> Mesh::Create(std::vector<Vertex>& p_vertices, const BufferLayout& p_bufferLayout, std::vector<uint32_t>& p_indices, std::vector<std::shared_ptr<Texture>>& p_textures) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				CC_CORE_INFO("The renderer API is not supported");
				break;

			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLMesh>(p_vertices, p_bufferLayout, p_indices, p_textures);
				break;
		}
	}
}