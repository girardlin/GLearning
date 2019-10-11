#include "TestTriangle.h"

#include "imgui.h"

namespace test {

	TestTriangle::TestTriangle()
		: m_Vertices{   //positions			  //colors
						-0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,
						 0.0f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,
						 0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f },
		  m_Index{ 0, 1, 2 }
	{
		/* VAO VBO setup*/
		m_VertexBuffer = new VertexBuffer(m_Vertices, 3 * 6 * sizeof(float));

		m_VertexBufferLayout = new VertexBufferLayout();
		m_VertexBufferLayout->Push<float>(3);
		m_VertexBufferLayout->Push<float>(3);

		m_VertexArray = new VertexArray();
		m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);

		/* Index Buffer setup */
		m_IndexBuffer = new IndexBuffer(m_Index, 3);

		/* Shader setup */
		m_Shader = new Shader("res/shaders/BasicColor.shader");

		/* Renderer setup */
		m_Renderer = new Renderer();
	}

	TestTriangle::~TestTriangle()
	{
		m_VertexBuffer->Unbind();
		m_VertexArray->Unbind();
		m_IndexBuffer->Unbind();
		m_Shader->Unbind();

		delete m_VertexBuffer;
		delete m_VertexArray;
		delete m_IndexBuffer;
		delete m_Shader;
		delete m_Renderer;
	}

	void TestTriangle::OnUpdate(float deltaTime)
	{

	}

	void TestTriangle::OnRender()
	{
		m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
	}

	void TestTriangle::OnImGuiRender() 
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
