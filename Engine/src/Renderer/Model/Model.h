#pragma once

#include "ccpch.h"
#include "Renderer/Mesh/Mesh.h"
#include "Renderer/Texture/Texture.h"

namespace Cannis {
	class Model {
	public:
		virtual ~Model() = default;

		virtual void Bind(uint32_t p_shaderID) = 0;
		virtual std::vector<std::shared_ptr<Mesh>>& GetMeshes() = 0;
		virtual void AddTexture(size_t p_meshID, const std::string& p_path) = 0;

		static std::shared_ptr<Model> Create(const std::string& p_path);
	};
}