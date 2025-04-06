#include "GameObject.h"

GameObject::GameObject()
{
	m_Position = glm::vec3(0.0f, 0.0f, -20.0f);
	m_Rotation = glm::vec3(0);
	

	m_MoveSpeed = 3.0f;

}

GameObject::GameObject(const std::string& _modelPath, const std::string& _texturePath)
{

	m_Model = std::make_shared<Model>(_modelPath);
	m_Texture = std::make_shared<Texture>(_texturePath);
	m_Position = glm::vec3(0.0f, 0.0f, -20.0f);
	m_Rotation = glm::vec3(0);

	m_MoveSpeed = 3.0f;
}

GameObject::~GameObject()
{
}

void GameObject::Update(float _dt)
{

	if (m_EventHandler->GetMoveRight())
	{
		m_Position += glm::vec3(-1.0f, 0.0f, 0.0f) * m_MoveSpeed * _dt;
		
	}

	if (m_EventHandler->GetMoveLeft())
	{
		m_Position += glm::vec3(1.0f, 0.0f, 0.0f) * m_MoveSpeed * _dt;
	}

	if (m_EventHandler->GetMoveForward())
	{
		m_Position += glm::vec3(0.0f, 0.0f, 1.0f) * m_MoveSpeed * _dt;
	}

	if (m_EventHandler->GetMoveBack())
	{
		m_Position += glm::vec3(0.0f, 0.0f, -1.0f) * m_MoveSpeed * _dt;
	}


	

}

void GameObject::Draw(float _dt, std::shared_ptr<ShaderProgram> _shader)
{
	
	glBindVertexArray(m_Model->vao_id());
	glBindTexture(GL_TEXTURE_2D, m_Texture->id());

	

	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), m_Position);
	//modelMatrix = glm::rotate(modelMatrix, glm::radians(m_Rotation.z), glm::vec3(0, 1, 0));

	//m_Rotation.z += 1;

	_shader->SetUniform("u_Model", modelMatrix);


	glDrawArrays(GL_TRIANGLES, 0, m_Model->vertex_count());


	glBindVertexArray(0);
	glUseProgram(0);

}

void GameObject::SetShader(std::shared_ptr<ShaderProgram> _shader)
{
	m_Shader = _shader;
}

void GameObject::SetEventManager(std::shared_ptr<EventHandler> _eventHandler)
{
	m_EventHandler = _eventHandler;
}

std::shared_ptr<Model> GameObject::GetModel() const
{
	return m_Model;
}

std::shared_ptr<Texture> GameObject::GetTexture() const
{
	return m_Texture;
}
