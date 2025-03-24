#pragma once

#include <glm/glm.hpp>

class Light {
public:

	Light() = default;
	Light(glm::vec3 direction, float luminance, glm::vec4 colour = glm::vec4(1));
	Light(const Light& other) = delete;
	~Light() = default;

	Light& operator=(const Light& other) = delete;

	void SetLuminance(float lum);
	void SetDirection(glm::vec3 direction);
	void SetColour(glm::vec4 rgba);

	glm::vec3 GetLightVec();
	float GetLuminance();
	glm::vec4 GetColour();

protected:
	glm::vec3 luxVec = { 0,-1,0 }; //Straight down
	glm::vec4 colour = { 1,1,1,1 }; //Pure white
};