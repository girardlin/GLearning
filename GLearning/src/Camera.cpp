#include "Camera.h"

Camera::Camera()
{
	int windowWidth, windowHeight;
	GLCall(m_CurrentContext = glfwGetCurrentContext());
	GLCall(glfwGetFramebufferSize(m_CurrentContext, &windowWidth, &windowHeight));
	G_LastX = float(windowWidth);
	G_LastY = float(windowHeight);
	G_LastX /= 2;
	G_LastY /= 2;

	m_CameraPosition = glm::vec3( 0.0f,  0.0f,  3.0f );
	m_CameraFront	 = glm::vec3( 0.0f,  0.0f, -1.0f );
	m_CameraUp	     = glm::vec3( 0.0f,  1.0f,  0.0f );

	m_OffsetX = 0.0f;
	m_OffsetY = 0.0f;

	m_Yaw = 0.0f;
	m_Pitch = 0.0f;

	m_CameraSpeed = 0.0f;
	m_CameraSpeedMultiplier = 5.0f;
	m_CameraRotationSensitivity = 0.05f;

	m_Cursor = false;
	glfwSetInputMode(m_CurrentContext, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Camera::~Camera()
{

}

glm::mat4 const Camera::GetViewMatrix()
{
	return glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp);
}

float* Camera::GetCameraSpeedMultiplierAddress()
{
	return &m_CameraSpeedMultiplier;
}

void Camera::ProcessKeyboardInputs(const float& deltaTime)
{
	m_CameraSpeed = m_CameraSpeedMultiplier * deltaTime;

	if (glfwGetKey(m_CurrentContext, GLFW_KEY_W) == GLFW_PRESS) //forward
	{
		m_CameraPosition += m_CameraFront * m_CameraSpeed;
	}
	if (glfwGetKey(m_CurrentContext, GLFW_KEY_S) == GLFW_PRESS) //backward
	{
		m_CameraPosition -= m_CameraFront * m_CameraSpeed;
	}
	if (glfwGetKey(m_CurrentContext, GLFW_KEY_A) == GLFW_PRESS) //left
	{
		m_CameraPosition -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_CameraSpeed;
	}
	if (glfwGetKey(m_CurrentContext, GLFW_KEY_D) == GLFW_PRESS) //right
	{
		m_CameraPosition += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_CameraSpeed;
	}
	if (glfwGetKey(m_CurrentContext, GLFW_KEY_C) == GLFW_PRESS && m_Cursor) //toggle cursor on press
	{
		glfwSetInputMode(m_CurrentContext, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		m_Cursor = false;
	}
	if (glfwGetKey(m_CurrentContext, GLFW_KEY_C) == GLFW_RELEASE && !m_Cursor) //toggle cursor back on release
	{
		glfwSetInputMode(m_CurrentContext, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_Cursor = true;
	}
}

void Camera::ProcessMouseInputs(const float& offsetX, const float& offsetY)
{
	m_OffsetX = offsetX;
	m_OffsetY = offsetY;

	m_OffsetX *= m_CameraRotationSensitivity;
	m_OffsetY *= m_CameraRotationSensitivity;

	m_Yaw += m_OffsetX;
	m_Pitch += m_OffsetY;

	/* constrain pitch */
	if (m_Pitch > 89.0f)
		m_Pitch = 89.0f;
	if (m_Pitch < -89.0f)
		m_Pitch = -89.0f;

	/* set front vector to calculated direction */
	glm::vec3 front;
	front.x = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));
	front.y = sin(glm::radians(m_Pitch));
	front.z = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));
	m_CameraFront = glm::normalize(front);
}