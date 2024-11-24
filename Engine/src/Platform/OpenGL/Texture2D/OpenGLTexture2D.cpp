#include "ccpch.h"
#include "OpenGLTexture2D.h"

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

namespace Cannis {
    OpenGLTexture2D::OpenGLTexture2D(const std::string& p_path, TextureType p_type) : m_type(p_type), m_ID(0), m_width(0), m_height(0) {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(0);
        stbi_uc* data = stbi_load(p_path.c_str(), &width, &height, &channels, 0);

        if (!data) {
            CC_CORE_ERROR("Failed to load image with : " + p_path);
            return;
        }

        m_width = width;
        m_height = height;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
        glTextureStorage2D(m_ID, 1, GL_RGB8, m_width, m_height);


        GLenum format = channels == 3 ? GL_RGB : GL_RGBA;
        glTextureSubImage2D(m_ID, 0, 0, 0, m_width, m_height, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D() {
        glDeleteTextures(1, &m_ID);
    }

    uint32_t OpenGLTexture2D::GetWidth() const {
        return m_width;
    }

    uint32_t OpenGLTexture2D::GetHeight() const {
        return m_height;
    }

    TextureType OpenGLTexture2D::GetType() const {
        return m_type;
    }

    uint32_t OpenGLTexture2D::GetID() const {
        return m_ID;
    }

    const std::string& OpenGLTexture2D::GetPath() const {
        return m_path;
    }

    void OpenGLTexture2D::Bind() {
        glBindTexture(GL_TEXTURE_2D, m_ID);
    }

}