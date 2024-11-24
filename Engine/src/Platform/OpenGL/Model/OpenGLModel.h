#pragma once

#include "ccpch.h"
#include "Renderer/Model/Model.h"
#include "Renderer/Mesh/Mesh.h"
#include "Renderer/Texture/Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Cannis {
	class OpenGLModel : public Model {
	public:
		OpenGLModel(const std::string p_path);
		virtual ~OpenGLModel();

		void Bind(uint32_t p_shaderID) override;
		std::vector<std::shared_ptr<Mesh>>& GetMeshes() override;
		void AddTexture(size_t p_meshID, const std::string& p_path) override;

	private:
		void LoadModel(const std::string& p_path);
		void ProcessNode(aiNode* p_aiNode, const aiScene* p_aiScene);
		void ProcessMesh(aiMesh* p_mesh, const aiScene* p_aiScene);
		std::vector<std::shared_ptr<Texture>> LoadTextures(aiMaterial* p_material, aiTextureType p_texType, const std::string& p_typeName, TextureType p_type);

	private:
		std::vector<std::shared_ptr<Mesh>> m_meshes;
		std::vector<std::shared_ptr<Texture>> m_texturesLoaded;
	};
}