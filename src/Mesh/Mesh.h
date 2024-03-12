#pragma once

#include <vector>

#include "../Vertex/Vertex.h"
#include "../Texture/Texture.h"
#include "../Shaders/Shader.h"

using std::vector;
using std::string;

namespace Cannis {
	class Mesh {
		public:
			vector<Vertex> vertices;
			vector<unsigned int> indices;
			vector<Texture> textures;

			/* @brief */
			Mesh(const vector<Vertex>& p_vertices, const vector<unsigned int>& p_indices, const vector<Texture>& p_textures);
			~Mesh();

			/* @brief */
			void draw(const Shader& p_shader) const;

		private:
			unsigned int m_VAO;
			unsigned int m_VBO;
			unsigned int m_EBO;

			void setupMesh() const;

			string getTextureName(const TextureType& p_texture) const;
	};
}