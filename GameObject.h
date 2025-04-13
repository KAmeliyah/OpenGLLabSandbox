#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include "Model.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "EventHandler.h"
#include "Collider.h"
#include <memory>

struct GameObject
{

	//this could be made into a base class

	GameObject();

	GameObject(const std::string& _modelPath, const std::string& _texturePath);

	~GameObject();


	void Update(float _dt);

	void Draw(float _dt, std::shared_ptr<ShaderProgram> _shader);

	void OnCollision(std::shared_ptr<Collider> _other);


	void SetEventManager(std::shared_ptr<EventHandler> _eventHandler);

	void SetPosition(glm::vec3 _pos) { m_Position = _pos; }


	//Make copy so underlying object can be modified safely
	std::shared_ptr<Model> GetModel() const;
	std::shared_ptr<Texture> GetTexture() const;
	std::shared_ptr<Collider> GetCollider() const;

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();



private:

	std::shared_ptr<Model> m_Model{ nullptr };

	std::shared_ptr<Texture> m_Texture{ nullptr };


	std::shared_ptr<EventHandler> m_EventHandler{ nullptr };

	std::shared_ptr<Collider> m_Collider{ nullptr };

	glm::vec3 m_Position;

	//Use to find the forward direction
	glm::vec3 m_Rotation;


	float m_LastMouseX;
	float m_LastMouseY;
	float m_MoveSpeed;


};

#endif

