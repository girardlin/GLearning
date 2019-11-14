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

	class TestMaterial : public Test
	{
	private:
		float m_Vertices[6 * 6 * 8];

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ModelMatrix;
		glm::mat3 m_NormalMatrix;

		glm::vec3 m_Scale;
		glm::vec3 m_Rotation;
		glm::vec3 m_Translation;

		glm::vec3 m_LightPosition;

		glm::vec3 m_LightColor;

		float m_OrbitRadius;
		float m_RotationSpeed;
		float m_FOV;

		VertexBuffer* m_VertexBuffer;
		VertexBufferLayout* m_VertexBufferLayout;

		VertexArray* m_ObjectVertexArray;
		VertexArray* m_LampVertexArray;

		Shader* m_ObjectShader;
		Shader* m_LampShader;

		Texture* m_ObjectDiffuse;
		Texture* m_ObjectSpecular;
		Texture* m_LampTexture;

		Camera* m_Camera;

	public:
		TestMaterial();
		~TestMaterial();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}