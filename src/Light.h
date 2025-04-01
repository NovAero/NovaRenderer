#pragma once

#include <glm/glm.hpp>


class Light {
public:

	Light() = default;
	Light(const Light& other) = delete;
	virtual ~Light();

	Light& operator=(const Light& other) = delete;

	glm::vec3 GetAmbient() const;
	glm::vec3 GetDiffuse() const;
	glm::vec3 GetSpecular() const;

	void SetAmbient(glm::vec3 value);
	void SetDiffuse(glm::vec3 value);
	void SetSpecular(glm::vec3 value);

protected:

	glm::vec3 m_ambient = { 1,1,1 };
	glm::vec3 m_diffuse = { 1,1,1 };
	glm::vec3 m_specular = { 1,1,1 };

};

class DirLight : public Light {
public:
	DirLight() = default;
	DirLight(glm::vec4 dirAndStr, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	~DirLight();

	void SetDirection(glm::vec3 dir);
	void SetDirection(float x, float y, float z);
	void SetLuminance(float luminance);

	float GetLuminance();
	glm::vec3 GetDirection();

private:

	//Direction is xyz and luminance (strength) is w
	glm::vec4 m_dirNstr;
};

class PointLight : public Light {
public:

	PointLight() = default;
	PointLight(glm::vec4 posAndStr, glm::vec3 clq, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	~PointLight();

	void SetLuminance(float luminance);
	void SetPosition(glm::vec3 pos);
	void SetCoLinQuad(glm::vec3 clq);

	float GetLuminance() const;
	glm::vec3 GetPosition() const;

	glm::vec3 GetCoLinQuad() const;
	float GetConstant() const;
	float GetLinear() const;
	float GetQuadratic() const;

private:

	glm::vec4 m_posNstr;
	glm::vec3 m_coLiQuad;
};