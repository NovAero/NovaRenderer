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

struct Material {

	Material() = default;
	Material(std::string mtlName);
	Material(const Material& other) = delete;
	~Material();

	Material& operator=(const Material& other) = delete;

	void LoadFromFile(std::string fileName);
	void Apply(ShaderProgram* shader);

//private:

	glm::vec3 Ka, Kd, Ks;
	float specExpo;
};
