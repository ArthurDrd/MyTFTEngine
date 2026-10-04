#pragma once
#include <glm/glm.hpp>

namespace MyTFTEngine {
	class Camera {
	public:
		Camera(float fovDegrees, float aspectRatio, float nearClip, float farClip);

		void SetPosition(const glm::vec3& position);
		void SetTarget(const glm::vec3& target);
		void SetAspectRatio(float aspectRatio);

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		const glm::vec3& GetPosition() const { return m_Position; }

	private:
		void RecalculateViewMatrix();
		void RecalculateProjectionMatrix();

	private:
		float m_Fov;
		float m_AspectRatio;
		float m_NearClip;
		float m_FarClip;

		glm::vec3 m_Position{ 0.0f, 6.0f, 6.0f };
		glm::vec3 m_Target{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Up{ 0.0f, 1.0f, 0.0f };

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	};
}