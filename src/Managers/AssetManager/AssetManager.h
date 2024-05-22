#pragma once

#include "../../Texture/Texture.h"
#include "../../Mesh/Mesh.h"

#include <map>
#include <memory>

using Cannis::Texture;
using std::map;
using std::unique_ptr;
using std::shared_ptr;

namespace Cannis {
	// @brief 
	class AssetManager {
	public: 
		AssetManager();

		void addTexture(const Texture& p_newTexture);
		shared_ptr<Texture> getTexture();

		void addMesh();
		shared_ptr<Mesh> getMesh();

	private:
		map<string, Texture> m_loadedTextures;
		map<string, Mesh> m_loadedMeshes;
	};
}