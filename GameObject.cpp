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

void GameObject::Draw(float _dt, std::shared_ptr<ShaderProgram> _shader)
{
	
	glBindVertexArray(m_Model->vao_id());
	glBindTexture(GL_TEXTURE_2D, m_Texture->id());

	m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0, 0, -20));
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Rotation.z), glm::vec3(0, 1, 0));

	m_Rotation.z += 1;

	_shader->SetUniform("u_Model", m_ModelMatrix);


	glDrawArrays(GL_TRIANGLES, 0, m_Model->vertex_count());


	glBindVertexArray(0);
	glUseProgram(0);

}

std::shared_ptr<Model> GameObject::GetModel() const
{
	return m_Model;
}

std::shared_ptr<Texture> GameObject::GetTexture() const
{
	return m_Texture;
}
