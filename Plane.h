#pragma once
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <memory>
struct Plane
{

	Plane(glm::vec3 _position, glm::vec3 rotation);
	~Plane();

	//Procedurally textured
	void Draw(std::shared_ptr<ShaderProgram> _shader);

	GLuint vaoId();

private:

	std::vector<float> m_vertices;

	glm::vec3 m_position;
	glm::vec3 m_rotation;

	GLuint m_vaoId;
	GLuint m_vboId;
	bool m_dirty;


};

