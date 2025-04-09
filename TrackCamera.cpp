#include "TrackCamera.h"



TrackCamera::TrackCamera(int _windowWidth, int _windowHeight): Camera(_windowWidth, _windowHeight)
{

}

TrackCamera::~TrackCamera()
{

}

void TrackCamera::Update(float _dt)
{


	
	//Modify this to be behind the cat and to involve rotation

	m_Position = m_Target->GetPosition() + glm::vec3(0, 0, 30);



	m_View = glm::lookAt(m_Position,m_Target->GetPosition(), m_CameraUp);


}

void TrackCamera::SetTarget(std::shared_ptr<GameObject> _targetObject)
{

	m_Target = _targetObject;
}
