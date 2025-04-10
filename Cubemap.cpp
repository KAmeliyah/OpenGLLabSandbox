#include "Cubemap.h"

Cubemap::Cubemap()
{

}

Cubemap::Cubemap(const std::string& _modelPath, std::vector<std::string>& _texturePaths)
{
	m_Model = std::make_shared<Model>(_modelPath);
	m_Texture = std::make_shared<Texture>(_texturePaths);
}

Cubemap::~Cubemap()
{

}




void Cubemap::Draw(std::shared_ptr<ShaderProgram> _shader)
{

	glBindVertexArray(m_Model->vao_id());
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture->id());

	//_shader is bound in hte draw function where this is called

	glDrawArrays(GL_TRIANGLES, 0, m_Model->vertex_count());
	glBindVertexArray(0);
	glUseProgram(0);



}
