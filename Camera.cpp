#include "Camera.h"


Camera::Camera(int _windowWidth, int _windowHeight)
{

	//Pulled back 10 units
	m_Position = glm::vec3(0, 0, 10);
	
	m_Rotation = glm::vec3(0, 0, 0);
	
	//Camera targets the origin for now
	m_Target = glm::vec3(0, 0, 0);

	//Set up the direction the camera is pointing
	m_CameraDirection = glm::normalize(m_Position - m_Target);

	//Set the up direction for the camera
	m_CameraUp = glm::vec3(0, 1, 0);

	m_Projection = glm::perspective(glm::radians(45.0f), float(_windowWidth) / float(_windowHeight), 0.1f, 100.0f);

	m_View = glm::lookAt(m_Position, m_Target, m_CameraUp);
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

	//Use Event Manager to handle inputs



	
	

}

void Camera::SetTarget(glm::vec3 _targetPos)
{
	m_Target = _targetPos;
}

void Camera::SetEventManager(std::shared_ptr<EventHandler> _eventHandler)
{
	m_EventHandler = _eventHandler;
}

glm::mat4& Camera::GetProjection()
{
	return m_Projection;
}

glm::mat4& Camera::GetView()
{
	return m_View;
}


void Camera::SetPosition(float _x, float _y, float _z)
{
	m_Position = glm::vec3(_x, _y, _z);
}

void Camera::SetPosition(glm::vec3 _pos)
{
	m_Position = _pos;

}
