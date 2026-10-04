
#include "HexMesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace MyTFTGame
{
	HexMesh::HexMesh(float radius)
	{
		m_Vertices.clear();
		m_Vertices.reserve(7 * 3);

		// Center vertice
		for(int i=0; i < 3; ++i)
		{
			m_Vertices.push_back(0.0f);
		}

		// Hexagon vertices
		for (int i = 0; i < 6; ++i)
		{
			float angleDegree = 60.0f * i + 30.0f;
			float angleRad = glm::radians(angleDegree);

			// X, Y , Z coordinates of the vertex
			m_Vertices.push_back(radius * glm::cos(angleRad));
			m_Vertices.push_back(0.0f);
			m_Vertices.push_back(radius * glm::sin(angleRad));
		}

		// Indices for the triangles
		for(int i = 1; i <= 6; ++i)
		{
			m_Indices.push_back(0);
			m_Indices.push_back(i);
			m_Indices.push_back(i % 6 + 1);
		}
	}
}