#pragma once

#include "../../../Shaders/Shader.h"

#include <memory>

namespace Cannis {
	class Framebuffer {
	public:
		Framebuffer(int p_screenWidth, int p_screenHeight);

		// @brief 
		void resize(int p_newWidth, int p_newHeight);

		// @brief
		void update();

		// @brief
		void bind() const;

		// @brief
		void unbind() const;

		// @brief 
		void clean() const;

		unsigned int getTextureID() const;

	private:
		// @brief Frame Buffer Object | 
		unsigned int m_ID;
		
		// @brief Render Buffer Object | 
		unsigned int m_rbo;

		unsigned int m_quadVAO;
		unsigned int m_quadVBO;

		std::unique_ptr<Shader> m_framebufferShader;

		// @brief ID of the framebuffer's texture
		unsigned int m_textureColorBuffer;
	};
}