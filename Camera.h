#pragma once
#include <glm/ext.hpp>
#include <glm/glm.hpp>

struct Camera
{
	Camera();
	~Camera();
	
	void Move(float _dt);
	void Rotate(float _dt, float _angle, glm::vec3 _axis);
	void Update(float _dt);

	void SetPosition(float _x, float _y, float _z);
	void SetPosition(glm::vec3 _pos);

	void SetTarget(glm::vec3 _targetPos);


private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;

	glm::vec3 m_Target;
	glm::vec3 m_CameraDirection;

	glm::mat4 m_Projection;
	glm::mat4 m_View;


};

