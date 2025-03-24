#include "Light.h"
#include <glm/ext.hpp>

Light::Light(glm::vec3 direction, float luminance, glm::vec4 colour)
{
	luxVec = glm::normalize(direction) * luminance;
	this->colour = colour;
}

void Light::SetLuminance(float lum)
{
	luxVec = glm::normalize(luxVec);
	luxVec *= lum;
}

void Light::SetDirection(glm::vec3 direction)
{
	float mag = glm::length(luxVec);
	luxVec = direction * mag;
}

void Light::SetColour(glm::vec4 rgba)
{
	colour = rgba;
}

glm::vec3 Light::GetLightVec()
{
	return glm::normalize(luxVec);
}

float Light::GetLuminance()
{
	return glm::length(luxVec);
}

glm::vec4 Light::GetColour()
{
	return colour;
}
