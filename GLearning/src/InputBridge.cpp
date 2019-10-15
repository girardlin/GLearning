#include "InputBridge.h"

Camera* InputBridge::m_AffectedCamera = nullptr;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (G_FirstMouse)
	{
		G_LastX = xpos;
		G_LastY = ypos;
		G_FirstMouse = false;
	}

	InputBridge::GetCamera()->ProcessMouseInputs(xpos - G_LastX, G_LastY - ypos);

	G_LastX = xpos;
	G_LastY = ypos;
}

InputBridge::InputBridge()
{

}

InputBridge::~InputBridge()
{

}

void InputBridge::BindCamera(Camera* affectedCamera)
{
	m_AffectedCamera = affectedCamera;
	GLCall(glfwSetCursorPosCallback(glfwGetCurrentContext(), mouse_callback));
}

Camera* InputBridge::GetCamera()
{
	if (m_AffectedCamera)
		return m_AffectedCamera;
	return nullptr;
}

void InputBridge::UnbindCamera()
{
	m_AffectedCamera = nullptr;
	GLCall(glfwSetCursorPosCallback(glfwGetCurrentContext(), NULL));
}