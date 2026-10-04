#pragma once
#include <glm/glm.hpp>
#include "Application.h"

namespace MyTFTEngine {
	class Input {
	public:
		
		static bool IsMouseButtonPressed(int button);
		static glm::vec2 GetMousePosition();
	};
}