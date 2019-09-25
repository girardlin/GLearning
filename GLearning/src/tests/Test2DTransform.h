#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

namespace test {

	class Test2DTransform : public Test
	{
	private:
		float m_Vertices[20];
		unsigned int m_Index[6];

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ModelMatrix;
		glm::vec3 m_TranslationA;
		glm::vec3 m_ScaleA;
		glm::vec3 m_TranslationB;
		glm::vec3 m_ScaleB;

		VertexBuffer* m_VertexBuffer;
		VertexBufferLayout* m_VertexBufferLayout;
		VertexArray* m_VertexArray;

		IndexBuffer* m_IndexBuffer;

		Shader* m_Shader;

		Texture* m_Texture;

		Renderer* m_Renderer;

	public:
		Test2DTransform();
		~Test2DTransform();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}