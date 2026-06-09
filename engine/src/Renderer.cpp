#include <glad/glad.h>
#include "Renderer.h"

namespace MyTFTEngine {

	void Renderer::Init() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void Renderer::Clear(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::Draw(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader) {
		shader->Bind();

		vertexArray->Bind();

		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}