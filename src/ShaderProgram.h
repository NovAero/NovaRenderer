#pragma once

#include "Graphics.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>

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

private:
	GLuint shaderProgram = 0;
	GLuint fragmentShader = 0;
	GLuint vertexShader = 0;
};