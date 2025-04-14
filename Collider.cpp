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


	m_ColliderWidth = maxX - minX;
	m_ColliderHeight = maxY - minY;
	m_ColliderDepth = maxZ - minZ;

	m_HalfSize = glm::vec3(m_ColliderWidth / 2.0f, m_ColliderHeight / 2.0f, m_ColliderDepth / 2.0f);

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

	glm::vec3 otherCentre = _other->GetColliderCentre();
	glm::vec3 otherSize = _other->GetHalfSize();
	
	//x
	if (m_ColliderCentre.x > otherCentre.x)
	{
		if (otherCentre.x + otherSize.x < m_ColliderCentre.x - m_HalfSize.x)
		{
			return false;
		}
	}
	else
	{
		if (m_ColliderCentre.x + m_HalfSize.x < otherCentre.x - otherSize.x)
		{
			return false;
		}
	}

	//y
	if (m_ColliderCentre.y > otherCentre.y)
	{
		if (otherCentre.y + otherSize.y < m_ColliderCentre.y - m_HalfSize.y)
		{
			return false;
		}
	}
	else
	{
		if (m_ColliderCentre.y + m_HalfSize.y < otherCentre.y - otherSize.y)
		{
			return false;
		}
	}
	
	//z
	if (m_ColliderCentre.z > otherCentre.z)
	{
		if (otherCentre.z + otherSize.z < m_ColliderCentre.z - m_HalfSize.z)
		{
			return false;
		}
	}
	else
	{
		if (m_ColliderCentre.z + m_HalfSize.z < otherCentre.z - otherSize.z)
		{
			return false;
		}
	}

	
	return true; 

}


float Collider::GetColliderWidth() const
{
	return m_ColliderWidth;
}

float Collider::GetColliderHeight() const
{
	return m_ColliderHeight;
}

float Collider::GetColliderDepth() const
{
	return m_ColliderDepth;
}

glm::vec3 Collider::GetColliderCentre() const
{
	return m_ColliderCentre;
}

glm::vec3 Collider::GetHalfSize()
{
	return m_HalfSize;
}
