#include "GameObject.h"

GameObject::GameObject()
{
	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Rotation = glm::vec3(0);
	

	m_MoveSpeed = 3.0f;

}

GameObject::GameObject(const std::string& _modelPath, const std::string& _texturePath)
{

	m_Model = std::make_shared<Model>(_modelPath);
	m_Texture = std::make_shared<Texture>(_texturePath);

	m_MoveSpeed = 3.0f;
	m_Position = glm::vec3(0.0f, 0.0f, -0.0f);
	m_Rotation = glm::vec3(0.0f,0.0f,0.0f);

	m_Collider = std::make_shared<Collider>(m_Position, m_Model->GetVertexPositions());


}

GameObject::~GameObject()
{
}

void GameObject::Update(float _dt)
{
	
	m_Collider->Update(m_Position);

}

void GameObject::Draw(float _dt, std::shared_ptr<ShaderProgram> _shader)
{
	
	//This needs modifications in case there isn't a model
	glBindVertexArray(m_Model->vao_id());
	glBindTexture(GL_TEXTURE_2D, m_Texture->id());


	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), m_Position);

	
	modelMatrix = glm::rotate(modelMatrix, glm::radians(m_Rotation.x), glm::vec3(0, 1, 0));

	

	_shader->SetUniform("u_Model", modelMatrix);


	glDrawArrays(GL_TRIANGLES, 0, m_Model->vertex_count());


	glBindVertexArray(0);
	glUseProgram(0);

}


void GameObject::SetEventManager(std::shared_ptr<EventHandler> _eventHandler)
{
	m_EventHandler = _eventHandler;
}

void GameObject::SetPosition(glm::vec3 _pos)
{
	m_Position = _pos;
}

void GameObject::SetTexture(const std::string& _texturePath)
{
	m_Texture = std::make_shared<Texture>(_texturePath);
}

void GameObject::SetTexture(std::shared_ptr<Texture> _texture)
{
	m_Texture = _texture;
}

void GameObject::SetModel(const std::string& _modelPath)
{
	m_Model = std::make_shared<Model>(_modelPath);
	

}

std::shared_ptr<Model> GameObject::GetModel() const
{
	return m_Model;
}

std::shared_ptr<Texture> GameObject::GetTexture() const
{
	return m_Texture;
}

std::shared_ptr<Collider> GameObject::GetCollider() const
{
	return m_Collider;
}

glm::vec3 GameObject::GetPosition()
{
	return m_Position;
}

glm::vec3 GameObject::GetRotation()
{
	return m_Rotation;
}
