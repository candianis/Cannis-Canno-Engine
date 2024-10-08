#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Shaders/Shader.h"
#include "../Texture/Texture.h"
#include "../Vertex/Vertex.h"

#include <string>
#include <memory>
#include <vector>

using Cannis::Shader;
using Cannis::Texture;
using Cannis::Vertex;

using std::vector;
using std::string;
using std::shared_ptr;

namespace Cannis {
    class Mesh {
    public:
        // mesh Data
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture>* textures;

        // constructor
        Mesh(const vector<Vertex>& vertices, const vector<unsigned int>& indices, vector<Texture>* textures);

        // @brief render the mesh
        // @param shader Shader this mesh will use to render itself
        void draw(const shared_ptr<Shader> p_shader) const;

        // @brief Cleans all the buffers this mesh created
        void clean() const;

    private:
        // render data 
        unsigned int m_VBO, m_EBO, m_VAO;

        // @brief initializes all the buffer objects/arrays
        void setupMesh() const;

        // @brief 
        // @returns The texture's type as a string
        string getTextureName(const TextureType& p_texType) const;
    };
}