#include "Texture.h"

Texture::Texture(const std::string& _path)
{
	//why use a car when a bicycle does the trick
	unsigned char* data = stbi_load(_path.c_str(), &m_Size.x, &m_Size.y, NULL, 4);
	if (!data)
	{
		throw std::runtime_error("Couldn't load the image");
	}

	//copy raw data into a safe store vector
	for (int i = 0; i < m_Size.x * m_Size.y * 4; i++)
	{
		m_Data.push_back(data[i]);
	}

	free(data);
	m_Dirty = true;
	m_Id = 0;

}

Texture::Texture(const std::vector<std::string>& _facePaths)
{

	for (int i = 0; i < _facePaths.size(); i++)
	{

		//All the faces are the same size so storing the size of one face is enough
		unsigned char* data = stbi_load(_facePaths[i].c_str(), &m_Size.x, &m_Size.y, &m_Channels, 0);

		if (!data)
		{
			throw std::runtime_error("Couldn't load the image: " + _facePaths[i]);

		}

		for (int j = 0; j < m_Size.x * m_Size.y * m_Channels; j++)
		{
			m_Data.push_back(data[j]);
		}

		stbi_image_free(data);

	}

	m_Dirty = true;
	m_Id = 0;

	
}

Texture::Texture(glm::ivec2 _size): m_Dirty(true), m_Id(0), m_Size(_size)
{
	//preallocate space
	m_Data.resize(_size.x * _size.y * 4);

}


Texture::~Texture()
{
	if (m_Id)
	{
		glDeleteTextures(1, &m_Id);
	}
	
}

void Texture::SetSize(glm::ivec2 _size)
{
	m_Size = _size;
}

glm::ivec2 Texture::GetSize() const
{
	return m_Size;
}

void Texture::load(const std::string& _path)
{
	

	
	unsigned char* data = stbi_load(_path.c_str(), &m_Size.x, &m_Size.y, NULL, 4);
	if (!data)
	{
		throw std::runtime_error("Couldn't load the image");
	}

	//copy raw data into a safe store vector
	for (int i = 0; i < m_Size.x * m_Size.y * 4; i++)
	{
		m_Data.push_back(data[i]);
	}

	free(data);
	m_Dirty = true;
	m_Id = 0;
}

void Texture::load(const std::vector<std::string>& _facePaths)
{
	

	for (int i = 0; i < _facePaths.size(); i++)
	{

		//All the faces are the same size so storing the size of one face is enough
		unsigned char* data = stbi_load(_facePaths[i].c_str(), &m_Size.x, &m_Size.y, &m_Channels, 0);
		std::cout << m_Size.x << " " << m_Size.y << std::endl;
		
		if (!data)
		{
			throw std::runtime_error("Couldn't load the image: " + _facePaths[i]);

		}

		for (int j = 0; j < m_Size.x * m_Size.y * m_Channels; j++)
		{
			m_Data.push_back(data[j]);
		}

		stbi_image_free(data);

	}

	std::cout << m_Data.size() << std::endl;
	
	m_Dirty = true;
	m_Id = 0;
}

void Texture::SetPixel(glm::ivec2 _position, const glm::vec4& _color)
{
	
	for (int i = 0; i < 4; i++)
	{
		m_Data[(_position.x * _position.y * 4) + i] = _color[i];
	}



}

glm::vec4 Texture::GetPixel(glm::ivec2 _position) const
{
	glm::vec4 pixelColor{ 0,0,0,0 };

	for (int i = 0; i < 4; i++)
	{
		pixelColor[i] = m_Data[(_position.x * _position.y * 4) + i] ;
	}

	return pixelColor;
}

GLuint Texture::id()
{

	if (!m_Id)
	{
		glGenTextures(1, &m_Id);

		if (!m_Id)
		{
			throw std::runtime_error("Couldn't create the texture");
		}

	}
	
	
	if (m_Dirty)
	{
		glBindTexture(GL_TEXTURE_2D, m_Id);

		//upload the image data to the bound texture unit in the GPU
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Size.x, m_Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data.data());

		//Generate mipmap so the texture is mapped correctly
		glGenerateMipmap(GL_TEXTURE_2D);

		//Unbind the texture because operations on it are done
		glBindTexture(GL_TEXTURE_2D, 0);

		m_Dirty = false;
	}


	return m_Id;
}

//This uses jpgs so no alpha channel
GLuint Texture::id(int _faces)
{
	if (!m_Id)
	{
		glGenTextures(1, &m_Id);
		/*std::cout << "Created texture" << std::endl;
		std::cout << m_Id << std::endl;*/

		if (!m_Id)
		{
			throw std::runtime_error("Couldn't create the texture");
		}

	}

	if (m_Dirty)
	{

		std::cout << m_Id << std::endl;
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_Id);
	

		//GLenum bindErr = glGetError();
		//if (bindErr != GL_NO_ERROR) {
		//	std::cout << "OpenGL Error (after binding texture): " << bindErr << std::endl;
		//}

	

		//upload the image data to the bound texture unit in the GPU

		GLenum faceTargets[6] = {
		GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
		};

		int faceSize = m_Size.x * m_Size.y * m_Channels;
		//std::cout << faceSize << std::endl;

		for (int i = 0; i < _faces; i++)
		{
			const void* faceData = m_Data.data() + i * faceSize;
			//std::cout << faceData << std::endl;

			glTexImage2D(faceTargets[i], 0, GL_RGB, m_Size.x, m_Size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, faceData);

			//GLenum err = glGetError();

			/*if (err != GL_NO_ERROR)
			{
				std::cout << i << std::endl;
				std::cout << "OpenGL Error: " << err << std::endl;
			}*/

			
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	

		m_Dirty = false;
	}



	return m_Id;
}
