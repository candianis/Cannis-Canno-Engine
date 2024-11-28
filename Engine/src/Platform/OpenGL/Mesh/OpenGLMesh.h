#pragma once

#include "ccpch.h"
#include "Renderer/Mesh/Mesh.h"
#include "Renderer/VertexArray/VertexArray.h"
#include "Renderer/Texture/Texture.h"

#include <cstdint>

namespace Cannis {
	class OpenGLMesh : public Mesh {
	public:
		OpenGLMesh(std::shared_ptr<std::vector<Vertex>>& p_vertices, const BufferLayout& p_bufferLayout, std::shared_ptr<std::vector<uint32_t>>& p_indices, std::vector<std::shared_ptr<Texture>>& p_textures);
		virtual ~OpenGLMesh();

		// @brief Bind the current mesh to be drawn. The shader has to have been bound previously
		void Bind(const uint32_t p_shaderID) override;
		void UnBind() override;

		std::shared_ptr<VertexArray>& GetVAO() override;
		void AddTexture(std::shared_ptr<Texture>& p_texture) override;

	private:
		std::shared_ptr<VertexArray> m_vertexArray;
		std::vector<std::shared_ptr<Texture>> m_textures;
	};
}