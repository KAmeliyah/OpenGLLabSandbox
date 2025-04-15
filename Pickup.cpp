#include "Pickup.h"

Pickup::Pickup():GameObject()
{
}

Pickup::Pickup(const std::string& _modelPath)
{

	m_Model = std::make_shared<Model>(_modelPath);
	m_Color = glm::vec3(1.0f, 0.0f, 0.0f);
	m_Position = glm::vec3(0.0f, 2.0f, 0.0f);
	m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	m_Collider = std::make_shared<Collider>(m_Position, m_Model->GetVertexPositions());

}

Pickup::~Pickup()
{
}

void Pickup::Draw(float _dt, std::shared_ptr<ShaderProgram> _shader)
{

	glBindVertexArray(m_Model->vao_id());

	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), m_Position);


	_shader->SetUniform("u_Model", modelMatrix);


	glDrawArrays(GL_TRIANGLES, 0, m_Model->vertex_count());


	glBindVertexArray(0);
	glUseProgram(0);

}

void Pickup::SetColor(glm::vec3 _color)
{
	m_Color = _color;
}

glm::vec3 Pickup::GetColor()
{
	return m_Color;
}
