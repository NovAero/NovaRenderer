#include "Light.h"
#include <glm/ext.hpp>

void DirLight::SetDirection(glm::vec3 dir)
{
	dir = glm::normalize(dir); //ensure direction is normalized;
	dirNstr = glm::vec4(dir, dirNstr.w);
}

void DirLight::SetDirection(float x, float y, float z)
{
	SetDirection(glm::vec3(x, y, z));
}

void DirLight::SetLuminance(float luminance)
{
	dirNstr.w = luminance;
}

float DirLight::GetLuminance()
{
	return dirNstr.w;
}

glm::vec3 DirLight::GetDirection()
{
	return glm::vec3(dirNstr.x, dirNstr.y, dirNstr.z);
}

glm::vec3 Light::GetAmbient() const
{
	return ambient;
}

glm::vec3 Light::GetDiffuse() const
{
	return diffuse;
}

glm::vec3 Light::GetSpecular() const
{
	return specular;
}

void Light::SetAmbient()
{
}

void Light::SetDiffuse()
{
}

void Light::SetSpecular()
{
}
