#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include "Model.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include <memory>

struct GameObject
{

	GameObject();

	GameObject(const std::string& _modelPath, const std::string& _texturePath);

	~GameObject();

	void Update(float _dt);

	void Draw(float _dt);

	
	//Make copy so underlying object can be modified safely
	std::shared_ptr<Model> GetModel() const;
	std::shared_ptr<Texture> GetTexture() const;


private:

	std::shared_ptr<Model> m_Model{ nullptr };

	std::shared_ptr<Texture> m_Texture{ nullptr };

	
	glm::vec3 m_Position = glm::vec3(0);
	glm::mat4 m_ModelMat = glm::mat4(1.0);


};

#endif

