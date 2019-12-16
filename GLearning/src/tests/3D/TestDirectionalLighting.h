#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "InputManager.h"

#include "Renderer.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

namespace test {

	class TestDirectionalLighting : public Test
	{
	private:
		float m_Vertices[6 * 6 * 8];
		glm::vec3 m_CubePositions[10];

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ModelMatrix;
		glm::mat3 m_NormalMatrix;

		glm::vec3 m_Scale;
		glm::vec3 m_Rotation;
		glm::vec3 m_Translation;

		glm::vec3 m_LightColor;
		glm::vec3 m_LightDirection;

		float m_RotationSpeed;
		float m_FOV;

		VertexBuffer* m_VertexBuffer;
		VertexBufferLayout* m_VertexBufferLayout;

		VertexArray* m_ObjectVertexArray;

		Shader* m_ObjectShader;

		Texture* m_ObjectDiffuse;
		Texture* m_ObjectSpecular;

		Camera* m_Camera;

	public:
		TestDirectionalLighting();
		~TestDirectionalLighting();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}