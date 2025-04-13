#include "Collider.h"

Collider::Collider(glm::vec3& _centre, std::vector<glm::vec3>& _vertexPositions)
{
	//calculate bounds and set the centre (which is just the position)
	m_ColliderCentre = _centre;

	//Get the min x vertex position and Max X vertex position - the difference is the width
	// repeat for y and z for height and depth


	//for each face - get the position of each vertex and test to see if its the furthest on any axis
	float minX = 0;
	float minY = 0;
	float minZ = 0;

	float maxX = 0;
	float maxY = 0;
	float maxZ = 0;


	for (int vertex = 0; vertex < _vertexPositions.size(); vertex++)
	{
		if (_vertexPositions[vertex].x < minX)
		{
			minX = _vertexPositions[vertex].x;
		}
		else if (_vertexPositions[vertex].x > maxX)
		{
			maxX = _vertexPositions[vertex].x;
		}

		
		if (_vertexPositions[vertex].y < minY)
		{
			minY = _vertexPositions[vertex].y;
		}
		else if (_vertexPositions[vertex].y > maxY)
		{
			maxY = _vertexPositions[vertex].y;
		}

		//collider depth is messed up which is causing issues for the AABB
		if (_vertexPositions[vertex].z < minZ)
		{
			minZ = _vertexPositions[vertex].z;
		}
		else if (_vertexPositions[vertex].z > maxZ)
		{
			maxZ = _vertexPositions[vertex].z;
		}
		

	}

	std::cout << "max x: " << maxX << std::endl;
	std::cout << "min x: " << minX << std::endl;

	std::cout << "max y: " << maxY << std::endl;
	std::cout << "min y: " << minY << std::endl;

	std::cout << "max z: " << maxZ << std::endl;
	std::cout << "min z: " << minZ << std::endl;

	m_ColliderWidth = maxX - minX;
	m_ColliderHeight = maxY - minY;
	m_ColliderDepth = maxZ - minZ;



}

Collider::~Collider()
{
}

void Collider::Update(glm::vec3& _centre)
{

	m_ColliderCentre = _centre;

}

bool Collider::AABBCollision(std::shared_ptr<Collider> _other)
{

	float width = m_ColliderWidth / 2.0f;
	float height = m_ColliderHeight / 2.0f;
	float depth = m_ColliderDepth / 2.0f;

	glm::vec3 otherCentre = _other->GetColliderCentre();
	float otherWidth = _other->GetColliderWidth() / 2.0f;
	float otherHeight = _other->GetColliderHeight()/ 2.0f;
	float otherDepth = _other->GetColliderDepth() / 2.0f;
	
	
	//x
	if (m_ColliderCentre.x > otherCentre.x)
	{
		if (otherCentre.x + otherWidth < m_ColliderCentre.x - width)
		{
			return false;
		}
	}
	else
	{
		if (m_ColliderCentre.x + width < otherCentre.x - otherWidth)
		{
			return false;
		}
	}

	if (m_ColliderCentre.y > otherCentre.y)
	{
		if (otherCentre.y + otherHeight < m_ColliderCentre.y - height)
		{
			return false;
		}
	}
	else
	{
		if (m_ColliderCentre.y + height < otherCentre.y - otherHeight)
		{
			return false;
		}
	}
	
	if (m_ColliderCentre.z > otherCentre.z)
	{
		if (otherCentre.z + otherDepth < m_ColliderCentre.z - otherDepth)
		{
			return false;
		}
	}
	else
	{
		if (m_ColliderCentre.z + depth < otherCentre.z - otherDepth)
		{
			return false;
		}
	}

	//returning true when it isn't possible
	return true; 

}

float Collider::GetColliderWidth()
{
	return m_ColliderWidth;
}

float Collider::GetColliderHeight()
{
	return m_ColliderHeight;
}

float Collider::GetColliderDepth()
{
	return m_ColliderDepth;
}

glm::vec3& Collider::GetColliderCentre()
{
	return m_ColliderCentre;
}
