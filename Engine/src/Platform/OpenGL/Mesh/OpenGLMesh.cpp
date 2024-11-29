#include "ccpch.h"
#include "OpenGLMesh.h"

namespace Cannis {
	OpenGLMesh::OpenGLMesh(std::shared_ptr<std::vector<Vertex>>& p_vertices, const BufferLayout& p_bufferLayout, std::shared_ptr<std::vector<uint32_t>>& p_indices, std::vector<std::shared_ptr<Texture>>& p_textures) {
		m_vertexArray = VertexArray::Create();
        m_vertexArray->Bind();

		std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(p_vertices, p_vertices->size() * sizeof(Vertex));
		vertexBuffer->SetLayout(p_bufferLayout);
		m_vertexArray->AddVertexBuffer(vertexBuffer);

		std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(p_indices, p_indices->size() * sizeof(uint32_t));
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
        for (unsigned int i = 0; i < m_textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
            string name;
            TextureType texType = m_textures[i]->GetType();
            switch (texType) {
                case TextureType::DiffuseTex:
                    name = "diffuseMap";
                    break;

                case TextureType::SpecularTex:
                    name = "specularMap";
                    break;

                case TextureType::NormalTex:
                    name = "normalMap";
                    break;

                case TextureType::HeightTex:
                    name = "heightMap";
                    break;

                case TextureType::AlbedoTex:
                    name = "albedoMap";
                    break;

                case TextureType::MetallicTex:
                    name = "metallicMap";
                    break;

                case TextureType::RoughnessTex:
                    name = "roughnessMap";
                    break;

                case TextureType::AmbientOcclusionTex:
                    name = "aoMap";
            }

            // now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(p_shaderID, name.c_str()), i);
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