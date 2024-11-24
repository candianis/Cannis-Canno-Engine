#pragma once

#include "Renderer/Texture/Texture.h"

namespace Cannis {
	class OpenGLTexture2D : public Texture {
	public:
		OpenGLTexture2D(const std::string& p_path, TextureType p_type);
		virtual ~OpenGLTexture2D();

		uint32_t GetWidth() const override;
		uint32_t GetHeight() const override;
		TextureType GetType() const override;
		uint32_t GetID() const override;
		const std::string& GetPath() const override;

		void Bind() override;

	private:
		uint32_t m_ID;
		int m_width, m_height;
		TextureType m_type;
		std::string m_path;
	};
}