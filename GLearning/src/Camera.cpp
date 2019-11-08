#include "Camera.h"

Camera::Camera()
{
	GLCall(m_CurrentContext = glfwGetCurrentContext());

	/* Default Camera Properties */
	m_CameraPosition = glm::vec3( 0.0f,  0.0f,  3.0f );
	m_CameraFront	 = glm::vec3( 0.0f,  0.0f, -1.0f );
	m_CameraUp	     = glm::vec3( 0.0f,  1.0f,  0.0f );

	m_Yaw = -90.0f;
	m_Pitch = 0.0f;

	m_OffsetX = 0.0f;
	m_OffsetY = 0.0f;

	m_CameraSpeed = 0.0f;
	m_CameraSpeedMultiplier = 5.0f;
	m_CameraRotationSensitivity = 0.05f;

	/* Enable Cursor and set cursor to be visible by default */
	m_Cursor = true;
	glfwSetInputMode(m_CurrentContext, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

Camera::~Camera()
{

}

glm::mat4 const Camera::GetViewMatrix()
{
	return glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp);
}

glm::vec3 const Camera::GetCameraPosition()
{
	return m_CameraPosition;
}

float* Camera::GetCameraSpeedMultiplierAddress()
{
	return &m_CameraSpeedMultiplier;
}

void Camera::ProcessKeyboardInput(const e_CameraInput& cameraInput, const float& deltaTime)
{
	m_CameraSpeed = m_CameraSpeedMultiplier * deltaTime;

	if (cameraInput == FORWARD) //forward
	{
		m_CameraPosition += m_CameraFront * m_CameraSpeed;
	}
	if (cameraInput  == BACKWARD) //backward
	{
		m_CameraPosition -= m_CameraFront * m_CameraSpeed;
	}
	if (cameraInput == LEFT) //left
	{
		m_CameraPosition -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_CameraSpeed;
	}
	if (cameraInput == RIGHT) //right
	{
		m_CameraPosition += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_CameraSpeed;
	}
	if (cameraInput == TOGGLE_CURSOR_PRESS && m_Cursor) //hide cursor on pressing "c" and lock cursor within window
	{
		glfwSetInputMode(m_CurrentContext, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		m_Cursor = false;
	}
	if (cameraInput == TOGGLE_CURSOR_RELEASE && !m_Cursor) //show cursor on releasing "c" and unlock cursor
	{
		glfwSetInputMode(m_CurrentContext, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_Cursor = true;
	}
}

void Camera::ProcessMouseInputs(const float& offsetX, const float& offsetY)
{
	m_OffsetX = offsetX;
	m_OffsetY = offsetY;

	/* calculate how much mouse movement happened since the last frame in pixels and add it to rotation */
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