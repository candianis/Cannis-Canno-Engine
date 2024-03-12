#pragma once

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Shaders/Shader.h"
#include "../Mesh/Mesh.h"
#include "../Texture/Texture.h"

using std::vector;
using std::string;

namespace Cannis {
	class Model {
	public:
		Model(const char* p_modelName);
		Model(const char* p_modelName, const char* p_textureName);
		void draw(const Shader& p_shader) const;

	private:
		vector<Mesh> m_meshes;
		string m_directory;
		vector<Texture> m_loadedTextures;

		void loadModel(string p_modelName);
		void processNode(aiNode* p_node, const aiScene* p_scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* p_scene);
		vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType p_textureType);
	};
}

