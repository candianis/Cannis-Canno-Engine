#include "Framebuffer.h"

// Note: glad must always be included before GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using Cannis::Framebuffer;

Framebuffer::Framebuffer(int p_screenWidth, int p_screenHeight) {
	glGenFramebuffers(1, &m_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

	glGenTextures(1, &m_textureColorBuffer);
	glBindTexture(GL_TEXTURE_2D, m_textureColorBuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, p_screenWidth, p_screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureColorBuffer, 0);

	glGenRenderbuffers(1, &m_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, p_screenWidth, p_screenHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

	auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAMEBUFFER::NOT_COMPLETE: " << fboStatus << std::endl;

		auto glErrorInfo = glGetError();
		std::cout << "Error: " << glErrorInfo << std::endl;

		if (fboStatus == GL_FRAMEBUFFER_UNSUPPORTED)
			std::cout << "implementation is not supported by OpenGL driver " << fboStatus << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	m_framebufferShader = std::make_unique<Shader>("screenShader.vert", "screenShader.frag");

	m_framebufferShader->use();
	m_framebufferShader->setInt("screenTexture", 0);

	glGenVertexArrays(1, &m_quadVAO);
	glGenBuffers(1, &m_quadVBO);
	glBindVertexArray(m_quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void Framebuffer::resize(int p_newWidth, int p_newHeight) {
	glBindTexture(GL_TEXTURE_2D, m_textureColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, p_newWidth, p_newHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureColorBuffer, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, p_newWidth, p_newHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
}

void Cannis::Framebuffer::update() {
	m_framebufferShader->use();
	glBindVertexArray(m_quadVAO);
	glBindTexture(GL_TEXTURE_2D, m_textureColorBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Framebuffer::bind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
}

void Framebuffer::unbind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::clean() const {
	glDeleteBuffers(1, &m_quadVAO);
	glDeleteBuffers(1, &m_quadVBO);
	glDeleteRenderbuffers(1, &m_rbo);
	glDeleteFramebuffers(1, &m_ID);
}

unsigned int Cannis::Framebuffer::getTextureID() const {
	return m_textureColorBuffer;
}
