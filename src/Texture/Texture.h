#pragma once

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <map>

using std::string;

class Texture
{
public:
	unsigned int ID;
	/*@brief Creates a 2D texture and binds it to the current texture OpenGL will use to render an object.
	  @param fileName the name of the image inside the Textures folder in Assets. If the system is not found a pink image will be applied
	  @param textureWrapping the type of texture wrapping OpenGL will use for this specific texture. The default method is to repeat the texture, GL_REPEAT*/
	Texture(const string fileName, GLenum textureWrapping = GL_REPEAT);
	~Texture() = default;

	/*@brief Binds this texture as the currently active texture object*/
	void bind();
	/*@brief Unbinds this texture from OpenGL*/
	void unbind();
	/*Asks OpenGL to safely delete this texture*/
	void cleanUp();
	int getWidth() const;
	int getHeight() const;

private:
	int width;
	int height;
	//Image components in the file such as red|green|blue|alpha or grey|alpha
	int channelsInFile;

	/*@returns The appropiate format in GLenum according to the image's channels
	  @brief The type of the image such as jpg or png. GLenum */
	std::map<int, GLenum> imageTypeFormat = {
		{ 1, GL_RED},
		{ 3, GL_RGB},
		{ 4, GL_RGBA}
	};

};

