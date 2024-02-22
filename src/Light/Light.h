#pragma once

#include <glm/glm.hpp>



class Light
{
public:
	Light(glm::vec3 color);
	~Light() = default;

private:
	glm::vec3 lightColor;

};

