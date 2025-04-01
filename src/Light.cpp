#include "Light.h"
#include <glm/ext.hpp>

void Light::SetAmbient(glm::vec3 value)
{
	m_ambient = value;
}

void Light::SetDiffuse(glm::vec3 value)
{
	m_diffuse = value;
}

void Light::SetSpecular(glm::vec3 value)
{
	m_specular = value;
}



DirLight::DirLight(glm::vec4 dirAndStr, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
	: m_dirNstr(dirAndStr)
{
	SetAmbient(ambient * dirAndStr.w);
	SetDiffuse(diffuse * dirAndStr.w);
	SetSpecular(specular * dirAndStr.w);
}

DirLight::~DirLight()
{
}

void DirLight::SetDirection(glm::vec3 dir)
{
	dir = glm::normalize(dir); //ensure direction is normalized;
	m_dirNstr = glm::vec4(dir, m_dirNstr.w);
}

void DirLight::SetDirection(float x, float y, float z)
{
	SetDirection(glm::vec3(x, y, z));
}

void DirLight::SetLuminance(float luminance)
{
	m_dirNstr.w = luminance;
}

float DirLight::GetLuminance()
{
	return m_dirNstr.w;
}

glm::vec3 DirLight::GetDirection()
{
	return glm::vec3(m_dirNstr.x, m_dirNstr.y, m_dirNstr.z);
}

Light::~Light()
{
}

glm::vec3 Light::GetAmbient() const
{
	return m_ambient;
}

glm::vec3 Light::GetDiffuse() const
{
	return m_diffuse;
}

glm::vec3 Light::GetSpecular() const
{
	return m_specular;
}



PointLight::PointLight(glm::vec4 posAndStr, glm::vec3 clq, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
	: m_posNstr(posAndStr), m_coLiQuad(clq)
{
	SetAmbient(ambient * posAndStr.w);
	SetDiffuse(diffuse * posAndStr.w);
	SetSpecular(specular * posAndStr.w);
}

PointLight::~PointLight()
{
}

void PointLight::SetLuminance(float luminance)
{
	m_posNstr.w = luminance;
}

void PointLight::SetPosition(glm::vec3 pos)
{
	m_posNstr = glm::vec4(pos.x, pos.y, pos.z, m_posNstr.w);
}

void PointLight::SetCoLinQuad(glm::vec3 clq)
{
	m_coLiQuad = clq;
}

float PointLight::GetLuminance() const
{
	return m_posNstr.w;
}

glm::vec3 PointLight::GetPosition() const
{
	return glm::vec3(m_posNstr.z, m_posNstr.y, m_posNstr.z);
}

glm::vec3 PointLight::GetCoLinQuad() const
{
	return m_coLiQuad;
}

float PointLight::GetConstant() const
{
	return m_coLiQuad.x;
}

float PointLight::GetLinear() const
{
	return m_coLiQuad.y;
}

float PointLight::GetQuadratic() const
{
	return m_coLiQuad.z;
}
