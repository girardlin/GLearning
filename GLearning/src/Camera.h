#pragma once

#include "Renderer.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

static float G_LastX = 0.0f, G_LastY = 0.0f;

enum e_CameraInput
{
	FORWARD, BACKWARD, LEFT, RIGHT, TOGGLE_CURSOR_PRESS, TOGGLE_CURSOR_RELEASE
};

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
	glm::vec3 const GetCameraPosition();
	float* GetCameraSpeedMultiplierAddress();

	void ProcessKeyboardInput(const e_CameraInput& cameraInput, const float& deltaTime);
	void ProcessMouseInputs(const float& offsetX, const float& offsetY);
};