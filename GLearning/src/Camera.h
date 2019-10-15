#pragma once

#include "Renderer.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

static float G_LastX = 480.0f, G_LastY = 270.0f;
static bool G_FirstMouse = true;

class Camera
{
private:
	GLFWwindow* m_CurrentContext;

	glm::vec3 m_CameraPosition;
	glm::vec3 m_CameraFront;
	glm::vec3 m_CameraUp;

	float m_OffsetX;
	float m_OffsetY;

	float m_Yaw;
	float m_Pitch;

	float m_CameraSpeed;
	float m_CameraSpeedMultiplier;
	float m_CameraRotationSensitivity;

	bool m_Cursor;

public:
	Camera();
	~Camera();

	glm::mat4 const GetViewMatrix();
	float* GetCameraSpeedMultiplierAddress();

	void ProcessKeyboardInputs(const float& deltaTime);
	void ProcessMouseInputs(const float& offsetX, const float& offsetY);
};