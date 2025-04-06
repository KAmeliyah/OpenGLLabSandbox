#pragma once
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <memory>
#include "EventHandler.h"


//https://learnopengl.com/Getting-started/Camera

struct Camera
{
	Camera(int _windowWidth, int _windowHeight);
	~Camera();
	
	void Move(float _dt);
	void Rotate(float _dt, float _angle, glm::vec3 _axis);
	void Update(float _dt);

	void SetPosition(float _x, float _y, float _z);
	void SetPosition(glm::vec3 _pos);

	void SetEventManager(std::shared_ptr<EventHandler> _eventHandler);

	glm::mat4 GetProjection();
	glm::mat4 GetView();


private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;

	//horizontal axis
	float m_Pitch;

	//vertical axis
	float m_Yaw;

	glm::vec3 m_CameraDirection;

	glm::vec3 m_CameraUp;
	float m_CameraSpeed = 3.0f;

	glm::mat4 m_Projection;
	glm::mat4 m_View;

	std::shared_ptr<EventHandler> m_EventHandler{ nullptr };

};

