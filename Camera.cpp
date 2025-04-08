#include "Camera.h"


Camera::Camera(int _windowWidth, int _windowHeight)
{

	//Pulled back 10 units
	m_Position = glm::vec3(0, 0, 10);
	
	m_Rotation = glm::vec3(0, 0, 0);
	
	m_Pitch = 0.0f;
	m_Yaw = -90.0f;

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


void Camera::Move(float _dt)
{

}

void Camera::Rotate(float _dt, float _angle, glm::vec3 _axis)
{


}

void Camera::Update(float _dt)
{

	//https://learnopengl.com/Getting-started/Camera
	//For camera movement, rotate before moving 

	//rotation


	//https://gamedev.stackexchange.com/questions/139547/sdl2-mouse-camera-movement
	
	if (m_EventHandler->GetMouseMoving())
	{
		m_Yaw += m_EventHandler->GetMouseRelX() * 0.1;
		m_Pitch -= m_EventHandler->GetMouseRelY() * 0.1;
	}
	

	if (m_Pitch > 89.0f)
	{
		m_Pitch = 89.0f;
	}
	if (m_Pitch < -89.0f)
	{
		m_Pitch = -89.0f;
	}

	glm::vec3 direction;
	direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	direction.y = sin(glm::radians(m_Pitch));
	direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

	m_CameraDirection = glm::normalize(direction);

	//position
	glm::vec3 rightVector = glm::normalize(glm::cross(m_CameraDirection, m_CameraUp));

	//Use Event Manager to handle inputs

	if (m_EventHandler->GetMoveRight())
	{
		m_Position += rightVector  * m_CameraSpeed * _dt;

	}

	if (m_EventHandler->GetMoveLeft())
	{
		m_Position -= rightVector * m_CameraSpeed * _dt;
	}

	if (m_EventHandler->GetMoveForward())
	{
		m_Position += m_CameraDirection * m_CameraSpeed * _dt;
	}

	if (m_EventHandler->GetMoveBack())
	{
		m_Position -= m_CameraDirection * m_CameraSpeed * _dt;
	}



	//view matrix
	m_View = glm::lookAt(m_Position, m_Position + m_CameraDirection, m_CameraUp);
	
	

}



void Camera::SetEventManager(std::shared_ptr<EventHandler> _eventHandler)
{
	m_EventHandler = _eventHandler;
}

glm::mat4 Camera::GetProjection()
{
	return m_Projection;
}

glm::mat4 Camera::GetView()
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
