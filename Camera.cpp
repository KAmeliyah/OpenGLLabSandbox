#include "Camera.h"

void Camera::SetTarget(glm::vec3 _targetPos)
{
	m_Target = _targetPos;
}

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Move(float _dt)
{
}

void Camera::Rotate(float _dt, float _angle, glm::vec3 _axis)
{
}

void Camera::Update(float _dt)
{
}

void Camera::SetPosition(float _x, float _y, float _z)
{
	m_Position = glm::vec3(_x, _y, _z);
}

void Camera::SetPosition(glm::vec3 _pos)
{
	m_Position = _pos;

}
