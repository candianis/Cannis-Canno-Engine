#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_FAILURE_STRING
#define STBI_FAILURE_USERMSG
#include <stb/stb_image.h>

Texture::Texture(const string fileName, GLenum textureWrapping) {
    glGenTextures(1, &ID);

    string filePath = "./Assets/Textures/" + fileName;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channelsInFile, 0);

    if (data) {
        string fileType = fileName.substr(fileName.find(".") + 1);
        
        //Bind the generate texture so that a texture image and a mipmap is assigned to it
        glBindTexture(GL_TEXTURE_2D, ID);

        //The second zero or the sixth parameter should always be 0
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, imageTypeFormat[channelsInFile], GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        //Set texture wrappings to GL_REPEAT
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapping);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapping);

        //When scaling a texture downwards, we linearly interpolate the two closest mipmaps
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //When scaling a texture upwards, bilinear filtering will be used
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    else {
        std::cout << "ERROR::TEXTURE::FILE_NOT_FOUND\n" << stbi_failure_reason() << std::endl;
        stbi_image_free(data);
        data = stbi_load("./Assets/Textures/default.jpg", &width, &height, &channelsInFile, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else {
            std::cout << "ERROR::TEXTURE::DEFAULT_TEXTURE_NOT_FOUND\n" << stbi_failure_reason() << std::endl;
        }
    }

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::UnBind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::GetWidth() const {
    return width;
}

int Texture::GetHeight() const {
    return height;
}