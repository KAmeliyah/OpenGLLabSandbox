#include "Texture.h"

Texture::Texture(const std::string& _path)
{
	//why use a car when a bicycle does the trick
	unsigned char* data = stbi_load(_path.c_str(), &m_size.x, &m_size.y, NULL, 4);
	if (!data)
	{
		throw std::runtime_error("Couldn't load the image");
	}

	//copy raw data into a safe store vector
	for (int i = 0; i < m_size.x * m_size.y * 4; i++)
	{
		m_data.push_back(data[i]);
	}

	free(data);
	m_dirty = true;
	m_id = 0;

}

Texture::Texture(glm::ivec2 _size): m_dirty(true), m_id(0), m_size(_size)
{
	//preallocate space
	m_data.resize(_size.x * _size.y * 4);

}

//Texture::Texture(const Texture& _copy)
//{
//
//}
//
//Texture& Texture::operator=(const Texture& _assign)
//{
//	
//}

Texture::~Texture()
{
	if (m_id)
	{
		glDeleteTextures(1, &m_id);
	}
	
}

void Texture::SetSize(glm::ivec2 _size)
{
	m_size = _size;
}

glm::ivec2 Texture::GetSize() const
{
	return m_size;
}

void Texture::load(const std::string& _path)
{
	int w = 0;
	int h = 0;

	//why use a car when a bicycle does the trick
	unsigned char* data = stbi_load(_path.c_str(), &m_size.x, &m_size.y, NULL, 4);
	if (!data)
	{
		throw std::runtime_error("Couldn't load the image");
	}

	//copy raw data into a safe store vector
	for (int i = 0; i < m_size.x * m_size.y * 4; i++)
	{
		m_data.push_back(data[i]);
	}

	free(data);
	m_dirty = true;
	m_id = 0;
}

void Texture::SetPixel(glm::ivec2 _position, const glm::vec4& _color)
{
	
	for (int i = 0; i < 4; i++)
	{
		m_data[(_position.x * _position.y * 4) + i] = _color[i];
	}



}

glm::vec4 Texture::GetPixel(glm::ivec2 _position) const
{
	glm::vec4 pixelColor{ 0,0,0,0 };

	for (int i = 0; i < 4; i++)
	{
		pixelColor[i] = m_data[(_position.x * _position.y * 4) + i] ;
	}

	return pixelColor;
}

GLuint Texture::id()
{

	if (!m_id)
	{
		glGenTextures(1, &m_id);

		if (!m_id)
		{
			throw std::runtime_error("Couldn't create the texture");
		}

	}
	
	
	if (m_dirty)
	{
		glBindTexture(GL_TEXTURE_2D, m_id);

		//upload the image data to the bound texture unit in the GPU
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data.data());

		//Generate mipmap so the texture is mapped correctly
		glGenerateMipmap(GL_TEXTURE_2D);

		//Unbind the texture because operations on it are done
		glBindTexture(GL_TEXTURE_2D, 0);

		m_dirty = false;
	}


	return m_id;
}
