#pragma once

#include <iostream>
#include <string>
#include <glad/glad.h>

using std::string;

class Texture
{
public:
	unsigned int ID;

	Texture(string fileName, GLenum textureWrapping);
	~Texture() = default;

	void Use();
	int GetWidth() const;
	int GetHeight() const;

private:
	int width;
	int height;
	//Image components in the file such as red|green|blue|alpha or grey|alpha
	int channelsInFile;
};

