#pragma once

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

#include "../Texture/Texture.h"
#include "../Mesh/Mesh.h"
#include "../Shaders/Shader.h"

#include <iostream>
#include <memory>
#include <vector>

using Cannis::Shader;
using Cannis::Mesh;
using std::vector;
using glm::vec3;

using std::shared_ptr;

class Model
{
public:
    Model();
    // @param path expects a filepath to a 3D model.
    // @param gamma 
    Model(const char* p_path, bool p_gamma = false);
    Model(const char* p_modelName, const char* p_textureName, bool p_flipTextureVertically = true, bool p_gamma = false);

    // @brief draws the model and all its meshes
    // @param shader Shader that will be applied to this model and all its meshes
    void draw(const shared_ptr<Shader> p_shader) const;

    // @brief 
    void addTexture(const char* p_textureName, bool p_flipTextureVertically = true);

    // @brief Deletes all textures and meshes of this model
    void clean();

private:
    // @brief all the meshes this model has
    vector<Mesh> m_meshes;
    // @brief path on disk of this model's file
    string m_directory;
    bool m_gammaCorrection;
    // @brief Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once. 
    vector<Texture> m_texturesLoaded;

    // @brief loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    // @param path path on disk where the model's file resides
    void loadModel(const string& p_path);

    //// @brief processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    //void processNode(aiNode* p_node, const aiScene* p_scene);

    ////@brief 
    //Mesh processMesh(aiMesh* p_mesh, const aiScene* p_scene);

    //// @brief checks all material textures of a given type and loads the textures if they're not loaded yet.
    //// @returns the required info is returned as a Texture struct.
    //vector<Texture> loadMaterialTextures(aiMaterial* p_mat, aiTextureType p_type, string p_typeName);
};