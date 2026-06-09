#pragma once

#include "VertexArray.h"
#include "Shader.h"
#include <memory>

namespace MyTFTEngine {
	
	class Renderer {
	public:
		// Initializes the rendering subsystem (e.g., OpenGL state)
		static void Init();

		// Clears the screen with the specified color
		static void Clear(float r, float g, float b, float a = 1.0f);

		// Draws the given vertex array using the specified shader
		static void Draw(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);
	};
}