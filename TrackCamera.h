#pragma once
#include "Camera.h"
#include "GameObject.h"

struct TrackCamera: Camera
{

	//This camera has target that it always stays on

	TrackCamera(int _windowWidth, int _windowHeight);
	~TrackCamera();

	void Update(float _dt);

	void SetTarget(std::shared_ptr<GameObject> _targetObject);

private:

	std::shared_ptr<GameObject> m_Target;



};

