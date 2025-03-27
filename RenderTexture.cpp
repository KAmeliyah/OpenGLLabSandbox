#include "RenderTexture.h"

RenderTexture::RenderTexture(int _width, int _height)
{
	m_Width = _width;
	m_Height = _height;
	m_FboId = 0;
	m_TexId = 0;
	m_RboId = 0;
	m_Dirty = true;
}

RenderTexture::~RenderTexture()
{

	glDeleteFramebuffers(1, &m_FboId);
	glDeleteTextures(1, &m_TexId);
	glDeleteRenderbuffers(1, &m_RboId);

}

void RenderTexture::Bind()
{
	if (!m_FboId)
	{
		glGenFramebuffers(1, &m_FboId);
		if (!m_FboId)
		{
			throw std::runtime_error("Failed to create a frame buffer object");
		}
	}

	if (!m_TexId)
	{
		glGenTextures(1, &m_TexId);
		if (!m_TexId)
		{
			throw std::runtime_error("Failed to create a texture");
		}
	}

	if (!m_RboId)
	{
		glGenRenderbuffers(1, &m_RboId);
		if (!m_RboId)
		{
			throw std::runtime_error("Failed to create a render buffer object");
		}
	}

	
	if (m_Dirty)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FboId);

		glBindTexture(GL_TEXTURE_2D, m_TexId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0,GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TexId, 0);

		glBindRenderbuffer(GL_RENDERBUFFER, m_RboId);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
		
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RboId);

		m_Dirty = false;

	}
	

}

void RenderTexture::Unbind()
{

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint RenderTexture::GetTexture()
{
	return m_TexId;
}
