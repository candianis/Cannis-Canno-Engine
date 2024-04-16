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
		void lateUpdate();

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

		// @brief Intermediate Render Buffer Object
		unsigned int m_intermediateFBO;
		unsigned int m_screenTexture;

		int m_textureWidth;
		int m_textureHeight;

		std::unique_ptr<Shader> m_framebufferShader;

		// @brief ID of the framebuffer's texture
		unsigned int m_textureColorBufferMultisampled;

		unsigned int m_screenVAO;
		unsigned int m_screenVBO;
		void setScreenArray();

		// @brief
		void createIntermediateFramebuffer();
	};
}