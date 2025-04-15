#include "Enemy.h"

Enemy::Enemy(): GameObject()
{
	m_Alerted = false;
}

Enemy::Enemy(const std::string& _modelPath, const std::string& _texturePath):GameObject(_modelPath, _texturePath)
{
	m_Alerted = false;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float _dt)
{

	//If the player is in their eyeline - chase

	//Using rays almost - they're ghosts they don't have to be very smart

	//otherwise patrol



	m_Collider->Update(m_Position);
}

void Enemy::Draw(float _dt, std::shared_ptr<ShaderProgram> _shader)
{
}
