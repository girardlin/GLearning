#include "TestTriangle.h"

#include "imgui.h"

namespace test {

	TestTriangle::TestTriangle()
		: m_Vertices{  //positions			  //colors
						-0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,
						 0.0f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,
						 0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f
					},
		m_Index{ 0, 1, 2 }
	{
		/* VAO VBO setup*/
		m_VertexBuffer.AssignData(m_Vertices, 3 * 6 * sizeof(float));
		m_VertexBufferLayout.Push<float>(3);
		m_VertexBufferLayout.Push<float>(3);
		m_VertexArray.AddBuffer(m_VertexBuffer, m_VertexBufferLayout);

		/* Index Buffer setup */
		m_IndexBuffer.AssignData(m_Index, 3);

		/* Shader setup */
		m_Shader.AssignData("res/shaders/Basic.shader");

		/* Unbind */
		m_VertexBuffer.Unbind();
		m_VertexArray.Unbind();
		m_IndexBuffer.Unbind();
		m_Shader.Unbind();
	}

	TestTriangle::~TestTriangle()
	{
		m_VertexBuffer.Unbind();
		m_VertexArray.Unbind();
		m_IndexBuffer.Unbind();
		m_Shader.Unbind();
	}

	void TestTriangle::OnUpdate(float deltaTime)
	{

	}

	void TestTriangle::OnRender()
	{
		m_Renderer.Draw(m_VertexArray, m_IndexBuffer, m_Shader);
	}

	void TestTriangle::OnImGuiRender() 
	{

	}
}
