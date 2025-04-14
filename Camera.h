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
	
	
	virtual void Update(float _dt);

	void SetPosition(float _x, float _y, float _z);
	void SetPosition(glm::vec3 _pos);
	void SetCameraSpeed(float _speed);

	void SetEventManager(std::shared_ptr<EventHandler> _eventHandler);

	glm::mat4 GetProjection() const;
	glm::mat4 GetView() const;
	glm::vec3 GetPosition() const;


protected:
	glm::vec3 m_Position;
	
	//vertical axis
	float m_Pitch;


	//horizontal axis
	float m_Yaw;


	glm::vec3 m_CameraDirection;

	glm::vec3 m_CameraUp;
	float m_CameraSpeed;

	glm::mat4 m_Projection;
	glm::mat4 m_View;


	std::shared_ptr<EventHandler> m_EventHandler{ nullptr };

};

