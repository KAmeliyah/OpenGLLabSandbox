#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(const std::string& _modelPath, const std::string& _texturePath):GameObject(_modelPath, _texturePath)
{
}

Enemy::~Enemy()
{
}

void Enemy::Update(float _dt)
{

	m_Collider->Update(m_Position);
}

void Enemy::Draw(float _dt, std::shared_ptr<ShaderProgram> _shader)
{
}
