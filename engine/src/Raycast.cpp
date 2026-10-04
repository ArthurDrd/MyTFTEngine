#include "Raycast.h"
#include <glm/gtc/matrix_transform.hpp>

namespace MyTFTEngine {
	
	Ray MyTFTEngine::Raycast::ScreenPointToRay(
		const glm::vec2& mousePos, 
		const glm::vec2& screenSize, 
		const glm::mat4& viewMatrix, 
		const glm::mat4& projectionMatrix)
	{
		glm::vec3 screenPosNear(mousePos.x, screenSize.y - mousePos.y, 0.0f);
		glm::vec3 screenPosFar(mousePos.x, screenSize.y - mousePos.y, 1.0f);

		glm::vec4 viewport(0.0f, 0.0f, screenSize.x, screenSize.y);

		glm::vec3 nearPoint = glm::unProject(screenPosNear, viewMatrix, projectionMatrix, viewport);
		glm::vec3 farPoint = glm::unProject(screenPosFar, viewMatrix, projectionMatrix, viewport);

		return Ray{ nearPoint, glm::normalize(farPoint - nearPoint) };
	}
	bool Raycast::RayIntersectsPlaneY(const Ray& ray, float groundY, glm::vec3& outIntersectionPoint)
	{
		if (glm::abs(ray.direction.y) == 0.0001f) {
			return false;
		}

		if ((groundY - ray.origin.y) / ray.direction.y >= 0) {
			outIntersectionPoint = ray.origin + (groundY - ray.origin.y) / ray.direction.y * ray.direction;
			return true;
		}
		return false;
	}
}