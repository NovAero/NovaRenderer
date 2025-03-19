#pragma once

#include "Graphics.h"
#include <glm/glm.hpp>
#include <string>

struct Texture {
public:
	Texture() : m_data(nullptr), m_width(0), m_height(0), m_channelCount(0) {}
	Texture(std::string fileName,int width, int height, int channelCount);

	Texture(const Texture& other) = delete;
	Texture& operator=(const Texture& other) = delete;

	~Texture();

	void Load(std::string fileName);

	GLuint texID = 0;

private:
	unsigned char* m_data;
	int m_width, m_height, m_channelCount;
};