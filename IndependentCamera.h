#include "Camera.h"

struct IndependentCamera: Camera
{

	IndependentCamera(int _windowWidth, int _windowHeight);
	
	void Update(float _dt) override;


private:
	float m_LastMouseX;
	float m_LastMouseY;


};

