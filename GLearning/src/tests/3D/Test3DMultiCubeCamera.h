#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "Renderer.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

namespace test {

	class Test3DMultiCubeCamera : public Test
	{
	private:
		float m_Vertices[6 * 6 * 5];
		glm::vec3 m_CubePositions[10];

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ModelMatrix;

		glm::vec3 m_Scale;
		glm::vec3 m_Rotation;
		glm::vec3 m_Translation;

		float m_RotationSpeed;
		float m_OrbitRadius;

		VertexBuffer* m_VertexBuffer;
		VertexBufferLayout* m_VertexBufferLayout;
		VertexArray* m_VertexArray;

		Shader* m_Shader;

		Texture* m_Texture;

		Renderer* m_Renderer;

	public:
		Test3DMultiCubeCamera();
		~Test3DMultiCubeCamera();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}