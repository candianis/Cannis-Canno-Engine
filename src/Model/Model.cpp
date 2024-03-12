#include <glm/glm.hpp>

#include "Model.h"

using Cannis::Model;
using glm::vec3;

Model::Model(const char* p_modelName) {
	loadModel(p_modelName);
}

Model::Model(const char* p_modelName, const char* p_textureName) {
	
}

void Model::draw(const Shader& p_shader) const {
	for (size_t i = 0; i < m_meshes.size(); ++i) {
		m_meshes[i].draw(p_shader);
	}
}

void Model::loadModel(string p_modelName) {
	Assimp::Importer importer;
	string filePath = "./Assets/3DModels/" + p_modelName;
	const aiScene* loadedScene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!loadedScene || loadedScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !loadedScene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}

	m_directory = filePath;
	processNode(loadedScene->mRootNode, loadedScene);
}

void Model::processNode(aiNode* p_node, const aiScene* p_scene) {
	for (size_t i = 0; i < p_node->mNumMeshes; ++i) {
		aiMesh* mesh = p_scene->mMeshes[p_node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, p_scene));
	}

	for (size_t i = 0; i < p_node->mNumChildren; ++i) {
		processNode(p_node->mChildren[i], p_scene);
	}
}

Cannis::Mesh Model::processMesh(aiMesh* mesh, const aiScene* p_scene) {
	vector<Vertex> vertices;
	for (size_t i = 0; i < mesh->mNumVertices; ++i) {
		Vertex vertex;

		//Process vertex position
		aiVector3D vertexPos = mesh->mVertices[i];
		vec3 position(vertexPos.x, vertexPos.y, vertexPos.z);
		vertex.position = position;

		//Process normal values
		if (mesh->HasNormals()) {
			aiVector3D normalVal = mesh->mNormals[i];
			vec3 normal(normalVal.x, normalVal.y, normalVal.z);
			vertex.normal = normal;
		}

		vertex.texCoord = glm::vec2(0.0f, 0.0f);

		//Process texture coordinates
		if (mesh->mTextureCoords[0]) {
			aiVector3D texCoordVal = mesh->mTextureCoords[0][i];
			glm::vec2 texCoord(texCoordVal.x, texCoordVal.y);
			vertex.texCoord = texCoord;
		}

		vertices.push_back(vertex);
	}

	vector<unsigned int> indices;
	for (size_t i = 0; i < mesh->mNumFaces; ++i) {
		const struct aiFace face = mesh->mFaces[i];
		for (size_t index = 0; index < face.mNumIndices; ++index)
			indices.push_back(face.mIndices[index]);
	}

	vector<Texture> textures;
	aiMaterial* material = p_scene->mMaterials[mesh->mMaterialIndex];

	vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	if (diffuseMaps.size() <= 0) {
		Texture texture("f117.png");
		texture.type = Diffuse;
		textures.push_back(texture);
	}

	vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR);
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	return Mesh(vertices, indices, textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType p_textureType) {
	vector<Texture> textures;
	for (size_t i = 0; i < mat->GetTextureCount(p_textureType); i++) {
		aiString filePath;
		mat->GetTexture(p_textureType, i, &filePath);

		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (size_t j = 0; j < m_loadedTextures.size(); j++) {
			if (std::strcmp(m_loadedTextures[j].filePath.data(), filePath.C_Str()) == 0) {
				textures.push_back(m_loadedTextures[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one.
				break;
			}
		}

		if (!skip) {   
			// if texture hasn't been loaded already, load it
			Texture texture(filePath.C_Str());
			textures.push_back(texture);
			m_loadedTextures.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't load a duplicated texture.
		}
	}
	
	return textures;
}