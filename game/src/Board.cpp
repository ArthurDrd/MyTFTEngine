#include "Board.h"
#include <HexMesh.h>
#include <Renderer.h>
#include <iostream>

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
        MyTFTEngine::BufferLayout layout = {
        { MyTFTEngine::ShaderDataType::Float3, "a_Position" }
            };
        vb->SetLayout(layout);

        auto ib = std::make_shared<MyTFTEngine::IndexBuffer>(
            hexMesh.GetIndices().data(),
            static_cast<unsigned int>(hexMesh.GetIndices().size())
        );

        m_HexVao->AddVertexBuffer(vb);
        m_HexVao->SetIndexBuffer(ib);

        float width = sqrt(3.0f) * m_HexRadius;
        float height = 1.5f * m_HexRadius;

        float totalWidth = BOARD_WIDTH * width;
        float totalHeight = BOARD_HEIGHT * height;
        float centerOffsetX = -totalWidth * 0.5f + (width * 0.5f);
        float centerOffsetZ = -totalHeight * 0.5f + (height * 0.5f);

        m_TileList.clear();

        for (int y = 0; y < BOARD_HEIGHT; ++y)
        {
            for (int x = 0; x < BOARD_WIDTH; ++x)
            {
                float xPos = x * width + ((y % 2 != 0) ? (width * 0.5f) : 0.0f) + centerOffsetX;
                float zPos = y * height + centerOffsetZ;

                m_TileList.push_back(Tile{ y, x, glm::vec3(xPos, 0.0f, zPos)});
                std::cerr << "Tile " << y * BOARD_WIDTH + x << " created at (" << x << ", " << y << ") with world position (" << xPos << ", 0.0, " << zPos << ")" << std::endl;
            }
        }
	}
    void Board::Render(const std::shared_ptr<MyTFTEngine::Shader>& shader)
    {
        shader->SetFloat("u_HexRadius", m_HexRadius);
     
        for (const auto& tile : m_TileList) {
            bool isHovered = (&tile == m_HoveredTile);
            
            float borderThickness = isHovered ? 0.35f : 0.12f;
            
            glm::vec4 fillColor = isHovered
                ? glm::vec4(1.0f, 0.9f, 0.2f, 0.25f)
                : glm::vec4(0.1f, 0.4f, 0.8f, 0.15f);
            
            glm::vec4 borderColor = isHovered
                ? glm::vec4(1.0f, 0.9f, 0.2f, 1.0f)
                : glm::vec4(0.2f, 0.7f, 1.0f, 0.7f);


            shader->SetFloat("u_BorderThickness", borderThickness);
            shader->SetVec4("u_FillColor", fillColor);
            shader->SetVec4("u_BorderColor", borderColor);

            glm::mat4 model = glm::translate(glm::mat4(1.0f), tile.worldPosition);
            shader->SetMat4("u_Model", model);;

            MyTFTEngine::Renderer::Draw(m_HexVao, shader);
        }
    }
    const Tile* Board::GetTileFromWorldPos(const glm::vec3& worldPos) const
    {
        const Tile* closestTile = nullptr;
        float minDistance = m_HexRadius;

        for (const auto& tile : m_TileList) {
            
            float distance = glm::distance(
                glm::vec2(tile.worldPosition.x, tile.worldPosition.z),
                glm::vec2(worldPos.x, worldPos.z));

            if (distance < minDistance) {
                minDistance = distance;
                closestTile = &tile;
            }
        }

        return closestTile;
    }
}