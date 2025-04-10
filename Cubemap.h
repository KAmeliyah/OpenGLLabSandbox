#pragma once

#include <vector>
#include <string>
#include "ShaderProgram.h"
#include "Model.h"

struct Cubemap
{
	//this isn't that different from game object
	Cubemap();
	Cubemap(const std::string& _modelPath, std::vector<std::string>& _texturePaths);

	~Cubemap();
	
	void Draw(std::shared_ptr<ShaderProgram> _shader);

private:

	//This is a simple cube obj
	std::shared_ptr<Model> m_Model;
	std::shared_ptr<Texture> m_Texture;


};

