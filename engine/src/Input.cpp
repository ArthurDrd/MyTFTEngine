#include "Input.h"
#include "Application.h"
#include <GLFW/glfw3.h>

namespace MyTFTEngine {

	bool Input::IsMouseButtonPressed(int button)
	{
		GLFWwindow* window = Application::Get().GetNativeWindow();
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		GLFWwindow* window = Application::Get().GetNativeWindow();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { static_cast<float>(xpos), static_cast<float>(ypos) };
	}
}