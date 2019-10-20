#pragma once

#include "Camera.h"

class InputManager
{
private:
	static Camera* m_AffectedCamera;
	static bool m_Jump;

	InputManager() { }
	~InputManager() { }

public:
	static Camera* GetCamera();

	static bool GetJump();
	static void SetJump(const bool& jump);

	static void BindCamera(Camera* affectedCamera);
	static void UnbindCamera();

	static void ProcessInputs(const float& deltaTime);
};