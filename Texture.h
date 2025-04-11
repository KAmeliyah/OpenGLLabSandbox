#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <stb_image.h>



struct Texture
{
	Texture(const std::string& _path);

	Texture(const std::vector<std::string>& _facePaths);
	Texture(glm::ivec2 _size);
	Texture(const Texture& _copy);
	Texture& operator=(const Texture& _assign);
	~Texture();

	void SetSize(glm::ivec2 _size);
	glm::ivec2 GetSize() const;

	void load(const std::string& _path);
	void load(const std::vector<std::string>& _facePaths);
	
	void SetPixel(glm::ivec2 _position, const glm::vec4& _color);
	glm::vec4 GetPixel(glm::ivec2 _position) const;

	//Not const because we aren't using GLuint until glew is initialised
	GLuint id();

	GLuint id(int _faces);

private:
	bool m_Dirty;
	std::vector<unsigned char> m_Data;
	glm::ivec2 m_Size;
	int m_Channels{ 0 };
	GLuint m_Id;

};
