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
	

	

	//glUseProgram(_shader->GetId());



	glBindVertexArray(m_Model->vao_id());
	



	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture->id(6));

	/*GLint width, height;
	glGetTexLevelParameteriv(GL_TEXTURE_CUBE_MAP_POSTIVE_X, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_CUBE_MAP_POSTIVE_X, 0, GL_TEXTURE_WIDTH, &height);*/


	//std::cout << m_Texture->id(6) << std::endl;

	//std::cout << m_Model->vertex_count() << std::endl;

	glDrawArrays(GL_TRIANGLES, 0, m_Model->vertex_count());
	glBindVertexArray(0);
	glUseProgram(0);



}
