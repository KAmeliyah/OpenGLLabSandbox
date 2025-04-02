#include "Camera.h"

void Camera::SetTarget(glm::vec3 _targetPos)
{
	m_Target = _targetPos;
}

void Camera::SetPosition(float _x, float _y, float _z)
{
	m_Position = glm::vec3(_x, _y, _z);
}

void Camera::SetPosition(glm::vec3 _pos)
{
	m_Position = _pos;

}
