#pragma once
#include <glm/glm.hpp> 

namespace MyTFTEngine {

	struct Ray {
		glm::vec3 origin;
		glm::vec3 direction;
	};

	class Raycast
	{
	public:
		static Ray ScreenPointToRay(
			const glm::vec2& mousePos,
			const glm::vec2& screenSize,
			const glm::mat4& viewMatrix,
			const glm::mat4& projectionMatrix
		);

		static bool RayIntersectsPlaneY(const Ray& ray, float groundY, glm::vec3& outIntersectionPoint);
	};
}