#include "Framebuffer.h"

// Note: glad must always be included before GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using Cannis::Framebuffer;

Framebuffer::Framebuffer(int p_screenWidth, int p_screenHeight) : m_textureWidth(p_screenWidth), m_textureHeight(p_screenHeight) {
	////Shader configuration
	//m_framebufferShader = std::make_unique<Shader>("screenShader.vert", "screenShader.frag");
	//m_framebufferShader->use();
	//m_framebufferShader->setInt("screenTexture", m_screenTexture);

	setScreenArray();

	glGenFramebuffers(1, &m_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

	glGenTextures(1, &m_textureColorBufferMultisampled);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_textureColorBufferMultisampled);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, m_textureWidth, m_textureHeight, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_textureColorBufferMultisampled, 0);

	glGenRenderbuffers(1, &m_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, m_textureWidth, m_textureHeight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
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

	createIntermediateFramebuffer();

}

void Framebuffer::resize(int p_newWidth, int p_newHeight) {
	m_textureWidth = p_newWidth;
	m_textureHeight = p_newHeight;

	glBindTexture(GL_TEXTURE_2D, m_screenTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textureWidth, m_textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_screenTexture, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, m_textureWidth, m_textureHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

}

void Framebuffer::update() {
	bind();
	// 3. now render quad with scene's visuals as its texture image
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//We clear the zbuffer as the model will change coordinates each cycle
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

void Framebuffer::lateUpdate() {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_ID);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_intermediateFBO);
	glBlitFramebuffer(0, 0, m_textureWidth, m_textureHeight, 0, 0, m_textureWidth, m_textureHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glEnable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_screenTexture); // use the now resolved color attachment as the quad's texture

	glDisable(GL_DEPTH_TEST);
	unbind();
}

void Framebuffer::bind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
}

void Framebuffer::unbind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::clean() const {
	glDeleteRenderbuffers(1, &m_rbo);
	glDeleteFramebuffers(1, &m_ID);
}

unsigned int Framebuffer::getTextureID() const {
	return m_screenTexture;
}

void Framebuffer::setScreenArray() {
	float quadVertices[] = {   // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &m_screenVAO);
	glGenBuffers(1, &m_screenVBO);
	glBindVertexArray(m_screenVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_screenVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void Framebuffer::createIntermediateFramebuffer() {
	glGenFramebuffers(1, &m_intermediateFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_intermediateFBO);

	glGenTextures(1, &m_screenTexture);
	glBindTexture(GL_TEXTURE_2D, m_screenTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textureWidth, m_textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_screenTexture, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Intermediate framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
