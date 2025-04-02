#include "GameObject.h"

GameObject::GameObject()
{


}

GameObject::GameObject(const std::string& _modelPath, const std::string& _texturePath)
{

	m_Model = std::make_shared<Model>(_modelPath);
	m_Texture = std::make_shared<Texture>(_texturePath);

}

GameObject::~GameObject()
{
}

void GameObject::Update(float _dt)
{
}

void GameObject::Draw(float _dt)
{
}

std::shared_ptr<Model> GameObject::GetModel() const
{
	return m_Model;
}

std::shared_ptr<Texture> GameObject::GetTexture() const
{
	return m_Texture;
}
