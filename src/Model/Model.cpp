#include <glm/glm.hpp>

#include "Model.h"


Model::Model() : m_gammaCorrection(false) {

}

Model::Model(const char* p_modelName, bool gamma) {
	loadModel(p_modelName);
	m_gammaCorrection = gamma;
}

Model::Model(const char* p_modelName, const char* p_textureName, bool p_flipTextureVertically, bool p_gamma) {
    loadModel(p_modelName);
    addTexture(p_textureName, p_flipTextureVertically);
    m_gammaCorrection = p_gamma;
}

void Model::draw(const shared_ptr<Shader> p_shader) const {
	for (size_t i = 0; i < m_meshes.size(); ++i) {
		m_meshes[i].draw(p_shader);
	}
}

void Model::clean() {
    for (int i = 0; i < m_meshes.size(); ++i) {
        m_meshes[i].clean();
    }

    for (int i = 0; i < m_texturesLoaded.size(); ++i) {
        m_texturesLoaded[i].cleanUp();
    }
}

void Model::addTexture(const char* p_textureName, bool p_flipTextureVertically) {    
    // check if texture was loaded all ready and exit early
    bool skip = false;
    for (unsigned int i = 0; i < m_texturesLoaded.size(); i++) {
        if (std::strcmp(m_texturesLoaded[i].path.data(), p_textureName) == 0) {
            return;
        }
    }

    //If it was not then we add the texture
    Texture texture(p_textureName, p_flipTextureVertically);
    texture.path = p_textureName;
    m_texturesLoaded.push_back(texture);
}

void Model::loadModel(const string& p_modelName) {
    // read file via ASSIMP
    Assimp::Importer importer;
    string filePath = "./Assets/3DModels/" + p_modelName;
    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    // retrieve the directory path of the filepath
    m_directory = p_modelName.substr(0, p_modelName.find_last_of('/'));

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
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

Mesh Model::processMesh(aiMesh* p_mesh, const aiScene* p_scene) {
    // data to fill
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < p_mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector(0); 
        // positions
        vector.x = p_mesh->mVertices[i].x;
        vector.y = p_mesh->mVertices[i].y;
        vector.z = p_mesh->mVertices[i].z;
        vertex.position = vector;
        // normals
        if (p_mesh->HasNormals())
        {
            vector.x = p_mesh->mNormals[i].x;
            vector.y = p_mesh->mNormals[i].y;
            vector.z = p_mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        // texture coordinates
        if (p_mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec(0,0);
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = p_mesh->mTextureCoords[0][i].x;
            vec.y = p_mesh->mTextureCoords[0][i].y;
            vertex.texCoord = vec;
            // tangent
            vector.x = p_mesh->mTangents[i].x;
            vector.y = p_mesh->mTangents[i].y;
            vector.z = p_mesh->mTangents[i].z;
            vertex.tangent = vector;
            // bitangent
            vector.x = p_mesh->mBitangents[i].x;
            vector.y = p_mesh->mBitangents[i].y;
            vector.z = p_mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        }
        else
            vertex.texCoord = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < p_mesh->mNumFaces; i++)
    {
        aiFace face = p_mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = p_scene->mMaterials[p_mesh->mMaterialIndex];

    // 1. diffuse maps
    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    Mesh newMesh(vertices, indices, &m_texturesLoaded);
    return newMesh;
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* p_mat, aiTextureType p_type, string p_typeName) {
    vector<Texture> textures;
    for (unsigned int i = 0; i < p_mat->GetTextureCount(p_type); i++) {
        aiString str;
        p_mat->GetTexture(p_type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for (unsigned int j = 0; j < m_texturesLoaded.size(); j++) {
            if (std::strcmp(m_texturesLoaded[j].path.data(), str.C_Str()) == 0) {
                textures.push_back(m_texturesLoaded[j]);
                skip = true; // texture with the same name has been loaded so we skip to the next one
                break;
            }
        }

        if (!skip) {   // if texture hasn't been loaded already, load it
            Texture texture(str.C_Str());
            texture.type = p_typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            m_texturesLoaded.push_back(texture);
        }
    }
    return textures;
}