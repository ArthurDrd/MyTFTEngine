#include "BoardLayer.h"
#include <Renderer.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

namespace MyTFTGame {
	BoardLayer::BoardLayer() : Layer("BoardLayer") {}

	void BoardLayer::OnAttach()
	{
		m_Shader = std::make_shared<MyTFTEngine::Shader>("assets/shaders/default.vert", "assets/shaders/default.frag");
		m_Board = std::make_unique<Board>(0.5f);
		
	}
	void BoardLayer::OnRender()
	{
		m_Shader->Bind();

		// Camera
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(
			glm::vec3(0.0f, 6.0f, 6.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

		m_Shader->SetMat4("u_ViewProjection", projection * view);

		m_Board->Render(m_Shader);
	}
	void BoardLayer::OnImGuiRender()
	{
		// TO DO
	}
}