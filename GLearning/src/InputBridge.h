#pragma once

#include "Camera.h"

class InputBridge
{
private:
	static Camera* m_AffectedCamera;

	InputBridge();
	~InputBridge();

public:
	static void BindCamera(Camera* affectedCamera);
	static Camera* GetCamera();
	static void UnbindCamera();
};