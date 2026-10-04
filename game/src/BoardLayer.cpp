#include "BoardLayer.h"
#include <Renderer.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <Input.h>
#include <Raycast.h>
#include <GLFW/glfw3.h>

namespace MyTFTGame {
	BoardLayer::BoardLayer() : Layer("BoardLayer"), m_Camera(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f) {
		m_Camera.SetPosition(glm::vec3(0.0f, 6.0f, 6.0f));
		m_Camera.SetTarget(glm::vec3(0.0f, 0.0f, 0.0f));
	}

	void BoardLayer::OnAttach()
	{
		m_Shader = std::make_shared<MyTFTEngine::Shader>("assets/shaders/hex.vert", "assets/shaders/hex.frag");
		m_Board = std::make_unique<Board>(0.5f);
		
	}
	void BoardLayer::OnUpdate(MyTFTEngine::Timestep ts)
	{
		glm::vec2 mousePos = MyTFTEngine::Input::GetMousePosition();
		glm::vec2 windowSize = MyTFTEngine::Application::Get().GetWindowSize();

		MyTFTEngine::Ray ray = MyTFTEngine::Raycast::ScreenPointToRay(
			mousePos,
			windowSize,
			m_Camera.GetViewMatrix(),
			m_Camera.GetProjectionMatrix()
		);

		glm::vec3 hitPoint;
		if (MyTFTEngine::Raycast::RayIntersectsPlaneY(ray, 0.0f, hitPoint))
        {
            const Tile* hoveredTile = m_Board->GetTileFromWorldPos(hitPoint);
            m_Board->SetHoveredTile(hoveredTile);
        }
        else
        {
            m_Board->SetHoveredTile(nullptr);
        }
	}
	void BoardLayer::OnRender()
	{
		m_Shader->Bind();

		m_Shader->SetMat4("u_ViewProjection", m_Camera.GetViewProjectionMatrix());

		m_Board->Render(m_Shader);
	}
	void BoardLayer::OnImGuiRender()
	{
		// TO DO
	}
}