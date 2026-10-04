#pragma once
#include <memory>
#include <glm/glm.hpp>

namespace MyTFTEngine {
	class VertexArray;
	class Shader;
}

struct Tile {
	int x, y;
	glm::vec3 worldPosition;
	bool isOccupied = false;
	bool isHovered = false;
};

namespace MyTFTGame
{
	class Board {
	public:
		Board(float hexRadius = 0.5f);
		~Board() = default;

		void Render(const std::shared_ptr<MyTFTEngine::Shader>& shader);

		const Tile* GetTileFromWorldPos(const glm::vec3& worldPos) const;
	private:
		static const int BOARD_WIDTH = 7;
		static const int BOARD_HEIGHT = 4;

		float m_HexRadius;
		std::shared_ptr<MyTFTEngine::VertexArray> m_HexVao;
		
		std::vector<Tile> m_TileList;
	};
}