#pragma once
#include <vector>

namespace MyTFTGame
{
	class HexMesh {
	public:
		HexMesh(float radius = 1.0f);
		~HexMesh() = default;

		const std::vector<float>& GetVertices() const { return m_Vertices; }
		const std::vector<unsigned int>& GetIndices() const { return m_Indices; }

	private:
		std::vector<float> m_Vertices;
		std::vector<unsigned int> m_Indices;
	}; 
}