#pragma once

#include <glm/glm.hpp>


class Light {
public:

	Light() = default;
	Light(const Light& other) = delete;
	virtual ~Light() = 0;

	Light& operator=(const Light& other) = delete;

	glm::vec3 GetAmbient() const;
	glm::vec3 GetDiffuse() const;
	glm::vec3 GetSpecular() const;

	void SetAmbient();
	void SetDiffuse();
	void SetSpecular();

protected:

	glm::vec3 ambient, diffuse, specular;

};


class DirLight : public Light {

	DirLight() = default;
	DirLight(glm::vec4 dirAndStr, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	~DirLight() = default;

	void SetDirection(glm::vec3 dir);
	void SetDirection(float x, float y, float z);
	void SetLuminance(float luminance);

	float GetLuminance();
	glm::vec3 GetDirection();

protected:

	//Direction is xyz and luminance (strength) is w
	glm::vec4 dirNstr;
};