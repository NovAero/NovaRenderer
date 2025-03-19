#include "Material.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(std::string fileName, int width, int height, int channelCount)
{
	m_width = width;
	m_height = height;
	m_channelCount = channelCount;

	Load(fileName);
}

Texture::~Texture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(m_data);
}

void Texture::Load(std::string fileName)
{
	m_data = stbi_load(fileName.c_str(), &m_width, &m_height, &m_channelCount, 0);

	glGenTextures(1, &texID);

	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);

	//glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

}
