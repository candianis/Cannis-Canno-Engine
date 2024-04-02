#pragma once

#include "../../Texture/Texture.h"

#include <map>
#include <memory>

using Cannis::Texture;
using std::map;
using std::unique_ptr;

namespace Cannis {
	// @brief 
	class AssetManager {
	public: 
		AssetManager();

		void addTexture(const Texture& p_newTexture);
		unique_ptr<Texture> getTexture();

	private:
		map<string, Texture> loadedTextures;
	};
}