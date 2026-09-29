#include "Board.h"

namespace MyTFTGame
{
	Board::Board(float hexRadius) : m_HexRadius(hexRadius)
	{
		MyTFTGame::HexMesh hexMesh(m_HexRadius);

        m_HexVao = std::make_shared<MyTFTEngine::VertexArray>();
        auto vb = std::make_shared<MyTFTEngine::VertexBuffer>(
            hexMesh.GetVertices().data(),
            static_cast<unsigned int>(hexMesh.GetVertices().size() * sizeof(float))
        );
        auto ib = std::make_shared<MyTFTEngine::IndexBuffer>(
            hexMesh.GetIndices().data(),
            static_cast<unsigned int>(hexMesh.GetIndices().size())
        );

        m_HexVao->AddVertexBuffer(vb);
        m_HexVao->SetIndexBuffer(ib);
	}
    void Board::Render(const std::shared_ptr<MyTFTEngine::Shader>& shader)
    {
		float width = sqrt(3.0f) * m_HexRadius;
		float height = 1.5f * m_HexRadius;
        
		float totalWidth = BOARD_WIDTH * width;
		float totalHeight = BOARD_HEIGHT * height;
        float centerOffsetX = -totalWidth * 0.5f + (width * 0.5f);
        float centerOffsetZ = -totalHeight * 0.5f + (height * 0.5f);

        for (int y = 0; y < BOARD_HEIGHT; ++y)
        {
            for (int x = 0; x < BOARD_WIDTH; ++x)
            {
                float xPos = x * width + ((y % 2 != 0) ? (width * 0.5f) : 0.0f) + centerOffsetX;
                float zPos = y * height + centerOffsetZ;

                glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(xPos, 0.0f, zPos));
                shader->SetMat4("u_Model", model);
                MyTFTEngine::Renderer::Draw(m_HexVao, shader);
            }
		}
    }
}
