#include "Material.h"
#include "Utilities.h"
#include <sstream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "ShaderProgram.h"


Texture::~Texture()
{
	glDeleteTextures(1, &texID);
}

void Texture::LoadFromFile(std::string fileName)
{
	int width, height, channelCount;

	unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &channelCount, 0);

	glGenTextures(1, &texID);

	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	//glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

void Texture::Bind(std::string name, ShaderProgram* shader, int texUnit) const
{
	shader->BindUniform(name, texUnit);
	glActiveTexture(GL_TEXTURE0 + texUnit);
	glBindTexture(GL_TEXTURE_2D, texID);
}


Material::Material(std::string matName)
{
	LoadFromFile(matName);
}

Material::~Material()
{

}

void Material::LoadFromFile(std::string fileName)
{
	std::fstream file(fileName, std::ios::in);
	std::string diff, spec, norm;
	std::string line;
	std::string header;
	char buffer[256];
	while (!file.eof())
	{
		file.getline(buffer, 256);
		line = buffer;
		std::stringstream ss(line,std::stringstream::in | std::stringstream::out);

		if (line.find("Ka") == 0) {
			ss >> header >> Ka.x >> Ka.y >> Ka.z;
		}
		else if (line.find("Ks") == 0) {
			ss >> header >> Ks.x >> Ks.y >> Ks.z;
		}
		else if (line.find("Kd") == 0) {
			ss >> header >> Kd.x >> Kd.y >> Kd.z;
		}
		else if (line.find("Ns") == 0) {
			ss >> header >> specExpo;
		}
		else if (line.find("map_Kd") == 0) {
			ss >> header >> diff;
		}
		else if (line.find("map_Ks") == 0) {
			ss >> header >> spec;
		}
		else if (line.find("bump") == 0) {
			ss >> header >> norm;
		}
	}
	if (diff != "") {
		m_diffuse = new Texture();
		m_diffuse->LoadFromFile(diff);
	}
	if (spec != "") {
		m_specular = new Texture();
		m_specular->LoadFromFile(spec);
	}
	if (norm != "") {
		m_normal = new Texture();
		m_normal->LoadFromFile(norm);
	}
}

void Material::Apply(ShaderProgram* shader)
{
	shader->BindUniform("material.ambient", Ka);
	shader->BindUniform("material.diffuse", Kd);
	shader->BindUniform("material.specular", Ks);
	shader->BindUniform("material.shininess", specExpo);

	if (m_diffuse) {
		m_diffuse->Bind("diffuseTex",shader, m_diffuse->texID);
	}
	if (m_specular) {
		m_specular->Bind("specularTex", shader, m_specular->texID);
	}
	if (m_normal) {
		m_normal->Bind("normalTex", shader, m_normal->texID);
	}
}
