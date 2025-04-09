#include "IndependentCamera.h"

IndependentCamera::IndependentCamera(int _windowWidth, int _windowHeight): Camera(_windowWidth, _windowHeight)
{
	m_LastMouseX = _windowWidth / 2.0f;
	m_LastMouseY = _windowHeight / 2.0f;
}


void IndependentCamera::Update(float _dt)
{

	//https://learnopengl.com/Getting-started/Camera
	//For camera movement, rotate before moving 

	//rotation

	//https://stackoverflow.com/questions/70843389/sdl2-mouse-capture
	//https://gamedev.stackexchange.com/questions/139547/sdl2-mouse-camera-movement

	if (m_EventHandler->GetMouseMoving())
	{
		float xOffset = (m_EventHandler->GetMouseX() - m_LastMouseX) * 0.1f;
		float yOffset = (m_LastMouseY - m_EventHandler->GetMouseY()) * 0.1f;

		m_LastMouseX = m_EventHandler->GetMouseX();
		m_LastMouseY = m_EventHandler->GetMouseY();


		m_Yaw += xOffset;
		m_Pitch += yOffset;


	}

	//https://www.reddit.com/r/opengl/comments/bjzm38/third_person_camera_opengl/
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
		m_Position += rightVector * m_CameraSpeed * _dt;

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


