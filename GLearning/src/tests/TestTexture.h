#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

namespace test {

	class TestTexture : public Test
	{
	private:
		float m_Vertices[20];
		unsigned int m_Index[6];

		VertexBuffer* m_VertexBuffer;
		VertexBufferLayout* m_VertexBufferLayout;
		VertexArray* m_VertexArray;

		IndexBuffer* m_IndexBuffer;

		Shader* m_Shader;

		Texture* m_Texture;

		Renderer* m_Renderer;

	public:
		TestTexture();
		~TestTexture();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}