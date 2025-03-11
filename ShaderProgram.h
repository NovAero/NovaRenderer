#pragma once

#include "Graphics.h"
#include <string>

class ShaderProgram {
public:
	ShaderProgram() {}
	ShaderProgram(std::string fragFilePath, std::string vertFilePath);

	~ShaderProgram();

	ShaderProgram(const ShaderProgram& other) = delete;
	ShaderProgram& operator=(const ShaderProgram& other) = delete;


private:
	GLuint shaderProgram = 0;
	
	GLuint fragmentShader = 0;
	GLuint vertexShader = 0;
};