#pragma once
#include <memory>
#include <glm/glm.hpp>

namespace MyTFTEngine {
	class VertexArray;
	class Shader;
}

namespace MyTFTGame
{
	class Board {
	public:
		Board(float hexRadius = 0.5f);
		~Board() = default;

		void Render(const std::shared_ptr<MyTFTEngine::Shader>& shader);

	private:
		static const int BOARD_WIDTH = 8;
		static const int BOARD_HEIGHT = 4;

		float m_HexRadius;
		std::shared_ptr<MyTFTEngine::VertexArray> m_HexVao;
	};
}