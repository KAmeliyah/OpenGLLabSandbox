#include "Player.h"

Player::Player(): GameObject()
{


}

Player::Player(const std::string& _modelPath, const std::string& _texturePath): GameObject(_modelPath, _texturePath)
{

	m_MoveSpeed = 3.0f;
	m_Position = glm::vec3(0.0f, 0.0f, 10.0f);
	m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Health = 100;
	m_Ammo = 100;


}

Player::~Player()
{
}

void Player::Update(float _dt)
{

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

void Player::Draw(float _dt, std::shared_ptr<ShaderProgram> _shader)
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

void Player::OnCollision(std::shared_ptr<Collider> _other)
{

	if (m_Collider->AABBCollision(_other))
	{

		glm::vec3 delta = m_Collider->GetColliderCentre() - _other->GetColliderCentre();

		glm::vec3 overlap = glm::vec3(
			(m_Collider->GetHalfSize().x + _other->GetHalfSize().x) - std::abs(delta.x),
			(m_Collider->GetHalfSize().y + _other->GetHalfSize().y) - std::abs(delta.y),
			(m_Collider->GetHalfSize().z + _other->GetHalfSize().z) - std::abs(delta.z));


		//Using collision normals similar to the impulse method from PFG
		if (overlap.x < overlap.y && overlap.x < overlap.z)
		{
			if (delta.x < 0)
			{
				m_Position.x -= overlap.x;
			}
			else
			{
				m_Position.x += overlap.x;
			}
		}
		else if (overlap.y < overlap.x && overlap.y < overlap.z)
		{
			if (delta.y)
			{
				m_Position.y -= overlap.y;

			}
			else
			{
				m_Position.y += overlap.y;
			}
		}
		else
		{
			if (delta.z < 0)
			{
				m_Position.z -= overlap.z;

			}
			else
			{
				m_Position.z += overlap.z;
			}
		}

		//Include further response based on type without needing to pass the thing itself
		switch (_other->GetType())
		{
			case 0:
				//Player - No response necessary
				break;

			case 1:
				//Enemy - Deal damage to self
				m_Health -= 10;
				break;

			case 2:
				//Bullet - Deal damage to self
				m_Health -= 10;
				break;

			case 3:
				//Health - replenish health
				m_Health += 30;

				if (m_Health > 100)
				{
					m_Health = 100;
				}

				break;

			case 4:
				//Speed - increase move speed for limited time
				break;
		}
	}
	


}

void Player::ModifyHealth(float _healthChange)
{
	m_Health += _healthChange;
}

bool Player::GetAlive() const
{
	if (m_Health < 0)
	{
		return false;
	}

	return true;
}

float Player::GetHealth() const
{
	return m_Health;
}

float Player::GetAmmo() const
{
	return m_Ammo;
}
