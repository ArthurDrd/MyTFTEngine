#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace MyTFTEngine {

    Camera::Camera(float fovDegrees, float aspectRatio, float nearClip, float farClip)
        : m_Fov(fovDegrees), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip)
    {
        RecalculateProjectionMatrix();
        RecalculateViewMatrix();
    }

    void Camera::SetPosition(const glm::vec3& position) {
        m_Position = position;
        RecalculateViewMatrix();
    }

    void Camera::SetTarget(const glm::vec3& target) {
        m_Target = target;
        RecalculateViewMatrix();
    }

    void Camera::SetAspectRatio(float aspectRatio) {
        m_AspectRatio = aspectRatio;
        RecalculateProjectionMatrix();
    }

    void Camera::RecalculateViewMatrix() {
        m_ViewMatrix = glm::lookAt(m_Position, m_Target, m_Up);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void Camera::RecalculateProjectionMatrix() {
        m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_NearClip, m_FarClip);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

}