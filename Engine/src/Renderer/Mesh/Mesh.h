#pragma once

#include "ccpch.h"
#include "Renderer/VertexArray/VertexArray.h"
#include "Renderer/Buffer/BufferLayout/BufferLayout.h"
#include "Renderer/Vertex/Vertex.h"
#include "Renderer/Texture/Texture.h"

namespace Cannis {
	class Mesh {
	public:
		virtual ~Mesh() = default;

		virtual void Bind(const uint32_t p_shaderID) = 0;
		virtual void UnBind() = 0;

		virtual std::shared_ptr<VertexArray>& GetVAO() = 0;
		virtual void AddTexture(std::shared_ptr<Texture>& p_texture) = 0;

		static std::shared_ptr<Mesh> Create(std::vector<Vertex>& p_vertices, const BufferLayout& p_bufferLayout, std::vector<uint32_t>& p_indices, std::vector<std::shared_ptr<Texture>>& p_textures);
	};
}