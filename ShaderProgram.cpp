#include "ShaderProgram.h"
#include <iostream>
#include "Utilities.h"

ShaderProgram::ShaderProgram(std::string fragFilePath, std::string vertFilePath)
{
	bool foundProblem = false;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	shaderProgram = glCreateProgram();

	std::string vertexSource = LoadFileAsString(vertFilePath);
	std::string fragmentSouce = LoadFileAsString(fragFilePath);

	if (vertexSource == "" || fragmentSouce == "") {
		std::cout << "Failed to open one or more shader files\n";
		std::cout << "Is your working directory set up properly?\n";
		foundProblem = true;
	}
	else {
		const char* vertexSourceC = vertexSource.c_str();

		glShaderSource(vertexShader, 1, &vertexSourceC, nullptr);
		glCompileShader(vertexShader);

		GLchar errorLog[512];
		GLint success = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			foundProblem = true;
			std::cout << "Something went wrong with the vertex shader!\n";
			glGetShaderInfoLog(vertexShader, 512, nullptr, errorLog);
			std::cout << errorLog << '\n';
		}
		else {
			std::cout << "\"" << fragFilePath << "\"" << " compiled successfully\n";
		}

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);

		glLinkProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			foundProblem = true;
			std::cout << "Error linking shaders\n";
			glGetShaderInfoLog(shaderProgram, 512, nullptr, errorLog);
		}
	}

	if (foundProblem) {

	}
}

ShaderProgram::~ShaderProgram()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(shaderProgram);
}

void ShaderProgram::Use()
{
	glUseProgram(shaderProgram);
}

void ShaderProgram::SetFloatUnifrom(std::string varName, float value)
{
	GLint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	glUniform1f(varLoc, value);
}
