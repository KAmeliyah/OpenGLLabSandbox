#pragma once
#include <GL/glew.h>
#include <stdexcept>
struct RenderTexture
{
	RenderTexture(int _width, int _height);
	~RenderTexture();

	RenderTexture(const RenderTexture& _copy);
	RenderTexture& operator=(const RenderTexture& _assign);

	void Bind();
	void Unbind();
	GLuint GetTexture();


private:
	int m_Width;
	int m_Height;
	GLuint m_FboId;
	GLuint m_TexId;
	GLuint m_RboId;
	bool m_Dirty;
	


};

