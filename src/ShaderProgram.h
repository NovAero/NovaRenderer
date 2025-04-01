#pragma once

#include "Graphics.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>

class PointLight;
class DirLight;
class Light;

class ShaderProgram {
public:
	ShaderProgram() {}
	ShaderProgram(std::string fragFilePath, std::string vertFilePath);
	ShaderProgram(const ShaderProgram& other) = delete;
	~ShaderProgram();

	ShaderProgram& operator=(const ShaderProgram& other) = delete;

	void Use();
	GLuint ID() { return shaderProgram; }

	//Uniform binds
	void BindUniform(std::string name, float value);
	void BindUniform(std::string name, int value);
	void BindUniform(std::string name, const glm::vec3& value);
	void BindUniform(std::string name, const glm::vec4& value);
	void BindUniform(std::string name, const glm::mat3& value);
	void BindUniform(std::string name, const glm::mat4& value);

	void BindPointLightArray(std::vector<Light*> lights, int from = 0);
	void BindPointLight(const PointLight& light, int index);
	void BindDirectionalLight(DirLight* light);

private:
	GLuint shaderProgram = 0;
	GLuint fragmentShader = 0;
	GLuint vertexShader = 0;
};