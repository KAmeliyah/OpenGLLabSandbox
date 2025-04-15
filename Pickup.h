#pragma once
#include "GameObject.h"
struct Pickup : public GameObject
{

	//Needs an enum for the type of pickup so I can make different colours
	//Ammo
	//Health
	//Speed

	Pickup();

	//No texture
	Pickup(const std::string& _modelPath);

	~Pickup();

	//No need to override the update since it doesn't move around

	void Draw(float _dt, std::shared_ptr<ShaderProgram> _shader) override;

	void SetColor(glm::vec3 _color);

	glm::vec3 GetColor();

private:

	//type of pickup
	glm::vec3 m_Color;


};

