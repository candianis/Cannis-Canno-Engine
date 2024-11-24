#include "ccpch.h"
#include "OpenGLMesh.h"

namespace Cannis {
	OpenGLMesh::OpenGLMesh(std::vector<Vertex>& p_vertices, const BufferLayout& p_bufferLayout, std::vector<uint32_t>& p_indices, std::vector<std::shared_ptr<Texture>>& p_textures) {
		m_vertexArray = VertexArray::Create();
        m_vertexArray->Bind();

		std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(p_vertices, p_vertices.size() * sizeof(Vertex));
		vertexBuffer->SetLayout(p_bufferLayout);
		m_vertexArray->AddVertexBuffer(vertexBuffer);

		std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(p_indices, p_indices.size() * sizeof(uint32_t));
		m_vertexArray->SetIndexBuffer(indexBuffer);

		m_textures = p_textures;
	}

    OpenGLMesh::~OpenGLMesh() {
        
    }

	void OpenGLMesh::Bind(const uint32_t p_shaderID) {
        // bind appropriate textures
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;
        for (unsigned int i = 0; i < m_textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            string number;
            string name;
            TextureType texType = m_textures[i]->GetType();
            switch (texType) {
                case TextureType::DiffuseTex:
                    number = std::to_string(diffuseNr++);
                    name = "texture_diffuse";
                    break;

                case TextureType::SpecularTex:
                    number = std::to_string(specularNr++); // transfer unsigned int to string
                    name = "texture_specular";
                    break;

                case TextureType::NormalTex:
                    number = std::to_string(normalNr++); // transfer unsigned int to string
                    name = "texture_normal";
                    break;

                case TextureType::HeightTex:
                    number = std::to_string(heightNr++); // transfer unsigned int to string
                    name = "texture_height";
                    break;
            }

            // now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(p_shaderID, (name + number).c_str()), i);

            m_textures[i]->Bind();
        }

		m_vertexArray->Bind();
	}

    void OpenGLMesh::UnBind() {
        m_vertexArray->UnBind();
        glActiveTexture(GL_TEXTURE0);
    }

    std::shared_ptr<VertexArray>& OpenGLMesh::GetVAO() {
        return m_vertexArray;
    }
    void OpenGLMesh::AddTexture(std::shared_ptr<Texture>& p_texture) {
        m_textures.push_back(p_texture);
    }
}