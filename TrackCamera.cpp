#include "TrackCamera.h"



TrackCamera::TrackCamera(int _windowWidth, int _windowHeight): Camera(_windowWidth, _windowHeight)
{

}

TrackCamera::~TrackCamera()
{

}

void TrackCamera::Update(float _dt)
{

	//if there is no target default to looking at the origin
	if (m_Target != nullptr)
	{
		m_CameraDirection = glm::normalize(m_Position - m_Target->GetPosition());
	}
	else
	{
		m_CameraDirection = glm::normalize(m_Position - glm::vec3(0));
	}
	

	m_View = glm::lookAt(m_Position, m_Position + m_CameraDirection, m_CameraUp);


}

void TrackCamera::SetTarget(std::shared_ptr<GameObject> _targetObject)
{

	m_Target = _targetObject;
}
