#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace test {
	
	class TestTriangle : public Test
	{
	private:
		float m_Vertices[18];
		unsigned int m_Index[3];

		VertexBuffer* m_VertexBuffer;
		VertexBufferLayout* m_VertexBufferLayout;
		VertexArray* m_VertexArray;

		IndexBuffer* m_IndexBuffer;

		Shader* m_Shader;

		Renderer* m_Renderer;

	public:
		TestTriangle();
		~TestTriangle();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}