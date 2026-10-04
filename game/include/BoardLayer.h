#pragma once
#include "Layer.h"
#include "Board.h"
#include "Shader.h"
#include <memory>
#include <Timestep.h>
#include <Camera.h>

namespace MyTFTGame {

	class BoardLayer : public MyTFTEngine::Layer {
	public:
		BoardLayer();
		~BoardLayer() override = default;

		void OnAttach() override;
		void OnUpdate(MyTFTEngine::Timestep ts) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<Board> m_Board;
		std::shared_ptr<MyTFTEngine::Shader> m_Shader;
		MyTFTEngine::Camera m_Camera;
	};
}