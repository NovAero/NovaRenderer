#pragma once
#include "Graphics.h"
#include <string>

class ShaderProgram;

struct Texture {

	GLuint texID = 0;

public:
	Texture() = default;
	Texture(const Texture& other) = delete;
	Texture& operator=(const Texture& other) = delete;
	~Texture();

	void LoadFromFile(std::string fileName);
	void Bind(std::string name, ShaderProgram* shader, int texUnit = 0) const;

};