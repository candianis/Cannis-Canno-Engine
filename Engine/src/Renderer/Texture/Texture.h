#pragma once

#include "ccpch.h"

namespace Cannis {
	enum class TextureType { DiffuseTex, SpecularTex, NormalTex, HeightTex, RoughnessTex, MetallicTex, AmbientOcclusionTex, AlbedoTex };

	class Texture {
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual TextureType GetType() const = 0;
		virtual uint32_t GetID() const = 0;
		virtual const std::string& GetPath() const = 0;

		virtual void Bind() = 0;

		static std::shared_ptr<Texture> Create(const std::string& p_path, TextureType p_type);
	};
}