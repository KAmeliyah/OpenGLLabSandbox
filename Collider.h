#pragma once
#include <memory>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include "Model.h"
#include <iostream>

struct Collider
{
	//Everyone gets a collider


	//Calculate height width and depth of the current object 
	Collider(glm::vec3& _centre, std::vector<glm::vec3>& _vertexPositions);
	~Collider();

	//This will be moved to the game object class once the collider is complete
	/*void OnCollisionEnter(Collider _other);
	void OnCollisionStay(Collider _other);
	void OnCollisionExit(Collider _other);*/

	//In case the scale of the object changes

	void Update(glm::vec3& _centre);

	void CalculateBounds(std::vector<glm::vec3>& _vertexPositions);

	bool AABBCollision(std::shared_ptr<Collider> _other);

	
	
	//tri-box collision?
	
	void SetColliderWidth(float _width);
	void SetColliderHeight(float _height);
	void SetColliderDepth(float _depth);

	float GetColliderWidth();
	float GetColliderHeight();
	float GetColliderDepth();
	glm::vec3& GetColliderCentre();


private:

	glm::vec3 m_ColliderCentre{ 0 };
	
	float m_ColliderWidth{ 0 };
	float m_ColliderHeight{ 0 };
	float m_ColliderDepth{ 0 };
	



};

