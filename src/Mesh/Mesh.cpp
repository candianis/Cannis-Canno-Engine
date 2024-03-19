#include "Mesh.h"

using Cannis::Mesh;

Mesh::Mesh(const vector<Vertex>& p_vertices, const vector<unsigned int>& p_indices, const vector<Cannis::Texture>& p_textures) {
	this->vertices = p_vertices;
	this->indices = p_indices;
	this->textures = p_textures;

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	setupMesh();
}

Mesh::~Mesh() {
	//glDeleteVertexArrays(1, &m_VAO);
	//glDeleteBuffers(1, &m_VBO);
	//glDeleteBuffers(1, &m_EBO);
}

void Mesh::draw(const Shader& p_shader) const {
	size_t diffuseAmount = 1;
	size_t specularAmount = 1;
	size_t normalAmount = 1;
	size_t heightAmount = 1;

	for (size_t i = 0; i < textures.size(); ++i) {
		glActiveTexture(GL_TEXTURE0 + i);
		
		string name = getTextureName(textures[i].textureType);
		string number = "";
		switch (textures[i].textureType) {
			case Diffuse:
				number = std::to_string(diffuseAmount++);
				break;

			case Specular:
				number = std::to_string(specularAmount++);
				break;

			case Normal:
				number = std::to_string(normalAmount);
				break;

			case Height:
				number = std::to_string(heightAmount);
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

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
	// ids
	glEnableVertexAttribArray(5);
	glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, boneIDs));

	// weights
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, weights));
	glBindVertexArray(0);
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
