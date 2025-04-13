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

	m_MoveSpeed = 3.0f;
	m_Position = glm::vec3(0.0f, 0.0f, -20.0f);
	m_Rotation = glm::vec3(0.0f,0.0f,0.0f);

	m_Collider = std::make_shared<Collider>(m_Position, m_Model->GetVertexPositions());


}

GameObject::~GameObject()
{
}

void GameObject::Update(float _dt)
{

	//calculate front and use it to move in the direction that the player is looking

	if (m_EventHandler->GetMouseMoving())
	{
		
		m_Rotation.x -= m_EventHandler->GetMouseX() * 0.1f;

	}


	float yawRadians = glm::radians(m_Rotation.x);

	glm::vec3 forward = glm::normalize(glm::vec3(sin(yawRadians), 0.0f, cos(yawRadians)));


	glm::vec3 rightVector = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));


	if (m_EventHandler->GetMoveRight())
	{
		m_Position += rightVector * m_MoveSpeed * _dt;
		
	}

	if (m_EventHandler->GetMoveLeft())
	{
		m_Position -= rightVector * m_MoveSpeed * _dt;
		
	}

	if (m_EventHandler->GetMoveForward())
	{
		m_Position += forward * m_MoveSpeed * _dt;
		
	}

	if (m_EventHandler->GetMoveBack())
	{
		m_Position -= forward * m_MoveSpeed * _dt;
		
	}


	m_Collider->Update(m_Position);

}

void GameObject::Draw(float _dt, std::shared_ptr<ShaderProgram> _shader)
{
	
	glBindVertexArray(m_Model->vao_id());
	glBindTexture(GL_TEXTURE_2D, m_Texture->id());

	

	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), m_Position);

	
	modelMatrix = glm::rotate(modelMatrix, glm::radians(m_Rotation.x), glm::vec3(0, 1, 0));

	

	_shader->SetUniform("u_Model", modelMatrix);


	glDrawArrays(GL_TRIANGLES, 0, m_Model->vertex_count());


	glBindVertexArray(0);
	glUseProgram(0);

}

void GameObject::OnCollision(std::shared_ptr<Collider> _other)
{
	if (m_Collider->AABBCollision(_other))
	{

		//Collision response
		std::cout << "Colliding" << std::endl;
	}



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

glm::vec3 GameObject::GetPosition()
{
	return m_Position;
}

glm::vec3 GameObject::GetRotation()
{
	return m_Rotation;
}
