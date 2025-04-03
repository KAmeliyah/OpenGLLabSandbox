#pragma once
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <memory>
#include "EventHandler.h"


struct Camera
{
	Camera(int _windowWidth, int _windowHeight);
	~Camera();
	
	void Move(float _dt);
	void Rotate(float _dt, float _angle, glm::vec3 _axis);
	void Update(float _dt);

	void SetPosition(float _x, float _y, float _z);
	void SetPosition(glm::vec3 _pos);

	void SetTarget(glm::vec3 _targetPos);

	void SetEventManager(std::shared_ptr<EventHandler> _eventHandler);

	glm::mat4& GetProjection();
	glm::mat4& GetView();


private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;

	glm::vec3 m_Target;
	glm::vec3 m_CameraDirection;

	glm::vec3 m_CameraUp;

	glm::mat4 m_Projection;
	glm::mat4 m_View;

	std::shared_ptr<EventHandler> m_EventHandler{ nullptr };

};

