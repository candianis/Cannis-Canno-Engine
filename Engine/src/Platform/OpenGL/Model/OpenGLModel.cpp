#include "ccpch.h"
#include "OpenGLModel.h"

namespace Cannis {
    OpenGLModel::OpenGLModel(const std::string p_path) {
        LoadModel(p_path);
    }

    OpenGLModel::~OpenGLModel()
    {
    }

    void OpenGLModel::Bind(uint32_t p_shaderID) {
        for (std::shared_ptr<Mesh> mesh : m_meshes) {
            mesh->Bind(p_shaderID);
        }
    }

    std::vector<std::shared_ptr<Mesh>>& OpenGLModel::GetMeshes() {
        return m_meshes;
    }

    void OpenGLModel::AddTexture(size_t p_meshID, const std::string& p_path) {
        std::shared_ptr<Texture> newTexture = Texture::Create(p_path, TextureType::DiffuseTex);

        m_meshes[p_meshID]->AddTexture(newTexture);
    }

    void OpenGLModel::LoadModel(const std::string& p_path) {
        Assimp::Importer import;
        const aiScene * scene = import.ReadFile(p_path, aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            CC_CORE_ERROR("ERROR::ASSIMP::" + std::string(import.GetErrorString()));
            return;
        }
        //directory = path.substr(0, path.find_last_of('/'));

        ProcessNode(scene->mRootNode, scene);
    }

    void OpenGLModel::ProcessNode(aiNode* p_aiNode, const aiScene* p_aiScene) {
        // process all the node's meshes (if any)
        for (unsigned int i = 0; i < p_aiNode->mNumMeshes; i++) {
            aiMesh* mesh = p_aiScene->mMeshes[p_aiNode->mMeshes[i]];
            ProcessMesh(mesh, p_aiScene);
        }

        // then do the same for each of its children
        for (unsigned int i = 0; i < p_aiNode->mNumChildren; i++) {
            ProcessNode(p_aiNode->mChildren[i], p_aiScene);
        }
    }

    void OpenGLModel::ProcessMesh(aiMesh* p_aiMesh, const aiScene* p_aiScene) {
        // data to fill
        std::shared_ptr<std::vector<Vertex>> vertices = std::make_shared<std::vector<Vertex>>();
        std::shared_ptr<std::vector<uint32_t>> indices = std::make_shared<std::vector<uint32_t>>();
        std::vector<std::shared_ptr<Texture>> textures;

        // walk through each of the mesh's vertices
        for (unsigned int i = 0; i < p_aiMesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            vector.x = p_aiMesh->mVertices[i].x;
            vector.y = p_aiMesh->mVertices[i].y;
            vector.z = p_aiMesh->mVertices[i].z;
            vertex.position = vector;

            // normals
            if (p_aiMesh->HasNormals())
            {
                vector.x = p_aiMesh->mNormals[i].x;
                vector.y = p_aiMesh->mNormals[i].y;
                vector.z = p_aiMesh->mNormals[i].z;
                vertex.normal = vector;
            }
            // texture coordinates
            if (p_aiMesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = p_aiMesh->mTextureCoords[0][i].x;
                vec.y = p_aiMesh->mTextureCoords[0][i].y;
                vertex.texCoord = vec;

                //// tangent
                //vector.x = mesh->mTangents[i].x;
                //vector.y = mesh->mTangents[i].y;
                //vector.z = mesh->mTangents[i].z;
                //vertex.Tangent = vector;
                //// bitangent
                //vector.x = mesh->mBitangents[i].x;
                //vector.y = mesh->mBitangents[i].y;
                //vector.z = mesh->mBitangents[i].z;
                //vertex.Bitangent = vector;
            }

            else
                vertex.texCoord = glm::vec2(0.0f, 0.0f);

            vertices->push_back(vertex);
        }

        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < p_aiMesh->mNumFaces; i++) {
            aiFace face = p_aiMesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices->push_back(face.mIndices[j]);
        }

        // process materials
        aiMaterial* material = p_aiScene->mMaterials[p_aiMesh->mMaterialIndex];
        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
        // Same applies to other texture as the following list summarizes:
        // diffuse: texture_diffuseN
        // specular: texture_specularN
        // normal: texture_normalN

        // 1. diffuse maps
        std::vector<std::shared_ptr<Texture>> diffuseMaps = LoadTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", TextureType::DiffuseTex);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        std::vector<std::shared_ptr<Texture>> specularMaps = LoadTextures(material, aiTextureType_SPECULAR, "texture_specular", TextureType::SpecularTex);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<std::shared_ptr<Texture>> normalMaps = LoadTextures(material, aiTextureType_HEIGHT, "texture_normal", TextureType::NormalTex);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<std::shared_ptr<Texture>> heightMaps = LoadTextures(material, aiTextureType_AMBIENT, "texture_height", TextureType::HeightTex);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        // Create buffer layout based on the model's information
        Cannis::BufferLayout bufferLayout = {
        	{ "a_Position", Cannis::ShaderDataType::Float3 },
        	{ "a_Normal", Cannis::ShaderDataType::Float3 },
        	{ "a_TexCoord", Cannis::ShaderDataType::Float2 }
        };

        std::shared_ptr<Mesh> newMesh = Mesh::Create(vertices, bufferLayout, indices, textures);
        m_meshes.push_back(newMesh);
    }

    std::vector<std::shared_ptr<Texture>> OpenGLModel::LoadTextures(aiMaterial* p_material, aiTextureType p_texType, const std::string& p_typeName, TextureType p_type) {
        std::vector<std::shared_ptr<Texture>> newTextures;

        for (size_t i = 0; i < p_material->GetTextureCount(p_texType); i++) {
            aiString str;
            p_material->GetTexture(p_texType, i, &str);
            
            bool skip = false;
            for (size_t i = 0; i < m_texturesLoaded.size(); i++) {
                if (std::strcmp(m_texturesLoaded[i]->GetPath().c_str(), str.C_Str()) == 0) {
                    newTextures.push_back(m_texturesLoaded[i]);
                    skip = true;
                    break;
                }
            }

            if (skip)
                continue;

            std::shared_ptr<Texture> newTexture = Texture::Create(str.C_Str(), p_type);
            newTextures.push_back(newTexture);
            m_texturesLoaded.push_back(newTexture);
        }

        return newTextures;
    }
}
