#pragma once
#include <glm/ext.hpp>
#include <glm/glm.hpp>

struct Camera
{
	Camera();
	~Camera();
	
	void Move();
	void Rotate();
	void LookAt();
	void Update();

private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;



};

