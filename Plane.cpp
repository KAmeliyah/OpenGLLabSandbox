#include "Plane.h"

Plane::Plane(glm::vec3 _position, glm::vec3 _rotation)
{
	//Plane Geometry

	m_position = _position;
	m_rotation = _rotation;

	m_vertices = {


		-1.0f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		 1.0f, 0.0f, -1.0f,	 0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		 1.0f, 0.0f,  1.0f,	 0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		-1.0f, 0.0f,  1.0f,	 0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		-1.0f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f, 	0.0f, 0.0f,
		 1.0f, 0.0f,  1.0f,	 0.0f, 1.0f, 0.0f,	1.0f, 1.0f,

	};


	m_dirty = true;
	m_vboId = 0;
	m_vaoId = 0;


}

Plane::~Plane()
{
}

void Plane::Draw(std::shared_ptr<ShaderProgram> _shader)
{


	//Do this base on rotation and stuff
	//glm::mat4 model = glm::rotate(model, glm::radians(angle), axis);
	//_shader->SetUniform(model);


	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glUseProgram(0);
}

GLuint Plane::vaoId()
{

	if (!m_vboId)
	{
		glGenBuffers(1, &m_vboId);

		if (!m_vboId)
		{
			throw std::runtime_error("Failed to generate plane vertex buffer");
		}
	}

	if (!m_vaoId)
	{
		glGenVertexArrays(1, &m_vaoId);

		if (!m_vaoId)
		{
			throw std::runtime_error("Failed to generate vertex array");
		}
	}

	if (m_dirty)
	{

		std::vector<GLfloat> data;

		for (size_t vi = 0; vi < m_vertices.size(); ++vi)
		{
			//Convert data into GLfloat
			data.push_back(m_vertices[vi]);
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data.at(0)), &data.at(0), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(m_vaoId);
		glBindBuffer(GL_ARRAY_BUFFER, m_vboId);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(data.at(0)), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
			8 * sizeof(data.at(0)), (void*)(3 * sizeof(GLfloat)));

		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
			8 * sizeof(data.at(0)), (void*)(5 * sizeof(GLfloat)));

		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_dirty = false;


	}

	return m_vaoId;
}
