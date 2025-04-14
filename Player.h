#pragma once
#include "GameObject.h"
struct Player : public GameObject
{


	Player();
	Player(const std::string& _modelPath, const std::string& _texturePath);
	~Player();

	void Update(float _dt) override;
	void Draw(float _dt, std::shared_ptr<ShaderProgram> _shader) override;

	float m_LastMouseX;
	float m_LastMouseY;
	float m_MoveSpeed;



};

