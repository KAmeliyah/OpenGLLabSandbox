#include "TrackCamera.h"



TrackCamera::TrackCamera(int _windowWidth, int _windowHeight): Camera(_windowWidth, _windowHeight)
{

}

TrackCamera::~TrackCamera()
{

}

void TrackCamera::Update(float _dt)
{

	//https://community.khronos.org/t/camera-that-follows-object-rotations/106743
	
	//Modify this to be behind the cat and to involve rotation

	//This camera should follow in front of the target. It should follow it when it moves and when it rotates
	//it should also rotate to be in front of the target.

	glm::vec3 targetRotation = m_Target->GetRotation();

	glm::vec3 direction;
	direction.x = sin(glm::radians(targetRotation.x));
	direction.y = 0.0f;
	direction.z = cos(glm::radians(targetRotation.x));

	glm::vec3 positionOffset = glm::normalize(direction) * 20.0f;

	m_Position = m_Target->GetPosition() - positionOffset + glm::vec3(0,8,0);


	//Convert euler rotation to a rotation matrix so it can be used with the view matrix
	glm::vec3 camTarget = m_Target->GetPosition() + glm::vec3(0, 3, 0);

	m_View = glm::lookAt(m_Position,camTarget, m_CameraUp);
	
	//combine position and rotation



}

void TrackCamera::SetTarget(std::shared_ptr<GameObject> _targetObject)
{

	m_Target = _targetObject;
}
