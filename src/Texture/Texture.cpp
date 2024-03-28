#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_FAILURE_STRING
#define STBI_FAILURE_USERMSG
#include <stb/stb_image.h>

Cannis::Texture::Texture(const string& p_fileName, bool flipVertically, GLenum p_textureWrapping) : textureType(None) {
    glGenTextures(1, &ID);

    string filePath = "./Assets/Textures/" + p_fileName;
    this->path = filePath;
    stbi_set_flip_vertically_on_load(flipVertically);

    unsigned char* data = stbi_load(filePath.c_str(), &m_width, &m_height, &m_channelsInFile, 0);

    if (data) {
        string fileType = p_fileName.substr(p_fileName.find(".") + 1);
        
        //Bind the generate texture so that a texture image and a mipmap is assigned to it
        glBindTexture(GL_TEXTURE_2D, ID);

        //The second zero or the sixth parameter should always be 0
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, m_imageTypeFormat[m_channelsInFile], GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        //Set texture wrappings to GL_REPEAT
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, p_textureWrapping);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, p_textureWrapping);

        //When scaling a texture downwards, we linearly interpolate the two closest mipmaps
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //When scaling a texture upwards, bilinear filtering will be used
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    else {
        std::cout << "ERROR::TEXTURE::FILE_NOT_FOUND\n" << stbi_failure_reason() << std::endl;
        stbi_image_free(data);
        data = stbi_load("./Assets/Textures/default.jpg", &m_width, &m_height, &m_channelsInFile, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else {
            std::cout << "ERROR::TEXTURE::DEFAULT_TEXTURE_NOT_FOUND\n" << stbi_failure_reason() << std::endl;
        }
    }

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Cannis::Texture::~Texture()
{
    
}

void Cannis::Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Cannis::Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Cannis::Texture::cleanUp() const {
    glDeleteTextures(1, &ID);
}

int Cannis::Texture::getWidth() const {
    return m_width;
}

int Cannis::Texture::getHeight() const {
    return m_height;
}