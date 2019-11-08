#include "InputManager.h"

Camera* InputManager::m_AffectedCamera = nullptr;
bool InputManager::m_Jump = true;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (InputManager::GetJump())
	{
		InputManager::GetCamera()->ProcessMouseInputs(0, 0);
		InputManager::SetJump(false);
	}
	else
	{
		InputManager::GetCamera()->ProcessMouseInputs(xpos - G_LastX, G_LastY - ypos);
	}
		
	G_LastX = xpos;
	G_LastY = ypos;
}

void InputManager::BindCamera(Camera* affectedCamera)
{
	m_AffectedCamera = affectedCamera;
	GLCall(glfwSetCursorPosCallback(glfwGetCurrentContext(), mouse_callback));
}

Camera* InputManager::GetCamera()
{
	if (m_AffectedCamera)
		return m_AffectedCamera;
	return nullptr;
}

bool InputManager::GetJump()
{
	return m_Jump;
}

void InputManager::SetJump(const bool& jump)
{
	m_Jump = jump;
}

void InputManager::UnbindCamera()
{
	m_AffectedCamera = nullptr;
	GLCall(glfwSetCursorPosCallback(glfwGetCurrentContext(), NULL));
}

void InputManager::ProcessInputs(const float& deltaTime)
{
	if (m_AffectedCamera == nullptr)
	{
		std::cout << "Cannot process inputs when no camera is bound to manager!" << std::endl;
		ASSERT(false);
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) //forward
	{
		m_AffectedCamera->ProcessKeyboardInput(FORWARD, deltaTime);
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) //backward
	{
		m_AffectedCamera->ProcessKeyboardInput(BACKWARD, deltaTime);
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) //left
	{
		m_AffectedCamera->ProcessKeyboardInput(LEFT, deltaTime);
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) //right
	{
		m_AffectedCamera->ProcessKeyboardInput(RIGHT, deltaTime);
	}
	if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) //toggle cursor on press
	{
		m_AffectedCamera->ProcessKeyboardInput(TOGGLE_CURSOR_PRESS, deltaTime);
		GLCall(glfwSetCursorPosCallback(glfwGetCurrentContext(), mouse_callback));
	}
	if (glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) //toggle cursor back on release
	{
		m_AffectedCamera->ProcessKeyboardInput(TOGGLE_CURSOR_RELEASE, deltaTime);
		GLCall(glfwSetCursorPosCallback(glfwGetCurrentContext(), NULL));
		m_Jump = true;
	}
}