#include "Camera.h"


Camera::Camera(int _windowWidth, int _windowHeight)
{

	//Pulled back 10 units
	m_Position = glm::vec3(0, 0, 10);
	
	m_Pitch = 0.0f;
	m_Yaw = -90.0f;

	m_CameraSpeed = 3.0f;

	//Set up the direction the camera is pointing
	m_CameraDirection = glm::normalize(glm::vec3(cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)),
						sin(glm::radians(m_Pitch)),
						sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch))));

	//Set the up direction for the camera
	m_CameraUp = glm::vec3(0, 1, 0);

	m_Projection = glm::perspective(glm::radians(45.0f), float(_windowWidth) / float(_windowHeight), 0.1f, 100.0f);

	
}

Camera::~Camera()
{
}


void Camera::SetEventManager(std::shared_ptr<EventHandler> _eventHandler)
{
	m_EventHandler = _eventHandler;
}

glm::mat4 Camera::GetProjection() const
{
	return m_Projection;
}

glm::mat4 Camera::GetView() const
{
	return m_View;
}

glm::vec3 Camera::GetPosition() const
{
	return m_Position;
}


void Camera::Update(float _dt)
{
	//view matrix
	m_View = glm::lookAt(m_Position, m_Position + m_CameraDirection, m_CameraUp);
}

void Camera::SetPosition(float _x, float _y, float _z)
{
	m_Position = glm::vec3(_x, _y, _z);
}

void Camera::SetPosition(glm::vec3 _pos)
{
	m_Position = _pos;

}

void Camera::SetCameraSpeed(float _speed)
{
	m_CameraSpeed = _speed;
}
