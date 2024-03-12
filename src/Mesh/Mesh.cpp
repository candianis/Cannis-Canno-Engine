#include <glad/glad.h>

#include "Mesh.h"

using Cannis::Mesh;

Mesh::Mesh(const vector<Vertex>& p_vertices, const vector<unsigned int>& p_indices, const vector<Texture>& p_textures) {
	this->vertices = p_vertices;
	this->indices = p_indices;
	this->textures = p_textures;

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	setupMesh();
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

void Mesh::draw(const Shader& p_shader) const {
	size_t m_diffuseAmount = 1;
	size_t m_specularAmount = 1;
	size_t m_normalAmount = 1;
	size_t m_heightAmount = 1;

	for (size_t i = 0; i < textures.size(); ++i) {
		glActiveTexture(GL_TEXTURE0 + i);
		
		string name = getTextureName(textures[i].type);
		string number = "";
		switch (textures[i].type) {
			case Diffuse:
				number = std::to_string(m_diffuseAmount++);
				break;

			case Specular:
				number = std::to_string(m_specularAmount++);
				break;

			case Normal:
				number = std::to_string(m_normalAmount);
				break;

			case Height:
				number = std::to_string(m_heightAmount);
				break;
		}
		name += number;

		p_shader.setInt(name, i);
		glBindTexture(GL_TEXTURE_2D, textures[i].ID);
	}

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh() const {
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//Set the vertex positions.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//Set the normal values. The name of the offset must be the same as the one inside the Vertex struct
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	//Set the texture coordinates.
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
}

string Mesh::getTextureName(const TextureType& p_texType) const {
	switch (p_texType) {
		case Diffuse:
			return "texture_diffuse";
			break;

		case Specular:
			return "texture_specular";
			break;

		default:
			return "";
			break;
	}

	return "";
}
