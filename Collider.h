#pragma once
#include <memory>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include "Model.h"
#include <iostream>

struct Collider
{
	//Everyone gets a collider
	//a collider type struct will be helpful in figuring out the correct response

	//Calculate height width and depth of the current object 
	Collider(glm::vec3& _centre, std::vector<glm::vec3>& _vertexPositions);
	~Collider();

	//In case the scale of the object changes

	void Update(glm::vec3& _centre);

	void CalculateBounds(std::vector<glm::vec3>& _vertexPositions);

	bool AABBCollision(std::shared_ptr<Collider> _other);

	glm::vec3 GetCollisionNormal(std::shared_ptr<Collider> _other);

	
	
	//tri-box collision?
	
	void SetColliderWidth(float _width);
	void SetColliderHeight(float _height);
	void SetColliderDepth(float _depth);

	float GetColliderWidth() const;
	float GetColliderHeight() const;
	float GetColliderDepth() const;
	glm::vec3 GetColliderCentre() const;
	glm::vec3 GetHalfSize();


private:

	glm::vec3 m_ColliderCentre;

	glm::vec3 m_HalfSize;
	
	float m_ColliderWidth{ 0 };
	float m_ColliderHeight{ 0 };
	float m_ColliderDepth{ 0 };
	



};

