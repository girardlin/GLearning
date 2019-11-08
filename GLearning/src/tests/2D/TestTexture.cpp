#include "TestTexture.h"

#include "imgui.h"

namespace test {

	TestTexture::TestTexture()
		: m_Vertices{   //positions			  //textures
						-0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
						 0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
						 0.5f,  0.5f,  0.0f,  1.0f,  1.0f,
						-0.5f,  0.5f,  0.0f,  0.0f,  1.0f },
						 m_Index{ 0, 1, 2, 2, 3, 0 }
	{
		/* VAO VBO setup*/
		m_VertexBuffer = new VertexBuffer(m_Vertices, 4 * 5 * sizeof(float));

		m_VertexBufferLayout = new VertexBufferLayout();
		m_VertexBufferLayout->Push<float>(3);
		m_VertexBufferLayout->Push<float>(2);

		m_VertexArray = new VertexArray();
		m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);

		/* Index Buffer setup */
		m_IndexBuffer = new IndexBuffer(m_Index, 6);
		
		/* Shader setup */
		m_Shader = new Shader("res/shaders/Basic.shader");

		m_Texture = new Texture("res/textures/gallade.png");
		m_Texture->Bind();
		m_Shader->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);

		/* Renderer setup */
		m_Renderer = new Renderer();
	}

	TestTexture::~TestTexture()
	{
		m_VertexBuffer->Unbind();
		m_VertexArray->Unbind();
		m_IndexBuffer->Unbind();
		m_Shader->Unbind();
		m_Texture->Unbind();

		delete m_VertexBuffer;
		delete m_VertexBufferLayout;
		delete m_VertexArray;
		delete m_IndexBuffer;
		delete m_Shader;
		delete m_Texture;
		delete m_Renderer;
	}

	void TestTexture::OnUpdate(float deltaTime)
	{

	}

	void TestTexture::OnRender()
	{
		m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
	}

	void TestTexture::OnImGuiRender()
	{
		ImGui::Text("Texture Test");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
