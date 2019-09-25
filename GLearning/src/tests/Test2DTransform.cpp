#include "Test2DTransform.h"

#include "imgui.h"

namespace test {

	Test2DTransform::Test2DTransform()
		: m_Vertices{   //positions		 //textures
						-50.0f, -50.0f,  0.0f,  0.0f,
						 50.5f, -50.5f,  1.0f,  0.0f,
						 50.5f,  50.5f,  1.0f,  1.0f,
						-50.5f,  50.5f,  0.0f,  1.0f },
						m_Index{ 0, 1, 2, 2, 3, 0 }
	{
		/* matrix setup */
		m_ProjectionMatrix = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		m_ModelMatrix = glm::mat4(1.0f);

		m_TranslationA = glm::vec3(240, 240, 0);
		m_ScaleA = glm::vec3(1.0, 1.0, 1.0);

		m_TranslationB = glm::vec3(720, 240, 0);
		m_ScaleB = glm::vec3(1.0, 1.0, 1.0);

		/* VAO VBO setup */
		m_VertexBuffer = new VertexBuffer(m_Vertices, 4 * 4 * sizeof(float));

		m_VertexBufferLayout = new VertexBufferLayout();
		m_VertexBufferLayout->Push<float>(2);
		m_VertexBufferLayout->Push<float>(2);

		m_VertexArray = new VertexArray();
		m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);

		/* Index Buffer setup */
		m_IndexBuffer = new IndexBuffer(m_Index, 6);

		/* Shader setup */
		m_Shader = new Shader("res/shaders/BasicMVP.shader");

		m_Texture = new Texture("res/textures/gallade.png");
		m_Texture->Bind();
		m_Shader->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);

		/* Renderer setup */
		m_Renderer = new Renderer();
	}

	Test2DTransform::~Test2DTransform()
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

	void Test2DTransform::OnUpdate(float deltaTime)
	{

	}

	void Test2DTransform::OnRender()
	{
		//Texture A
		{
			m_ModelMatrix = glm::translate(glm::mat4(1.0f), m_TranslationA);
			m_ModelMatrix = glm::scale(m_ModelMatrix, m_ScaleA);
			glm::mat4 mvp = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
			m_ModelMatrix = glm::mat4(1.0f);
		}
		//Texture B
		{
			m_ModelMatrix = glm::translate(glm::mat4(1.0f), m_TranslationB);
			m_ModelMatrix = glm::scale(m_ModelMatrix, m_ScaleB);
			glm::mat4 mvp = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
			m_ModelMatrix = glm::mat4(1.0f);
		}
		
	}

	void Test2DTransform::OnImGuiRender()
	{
		ImGui::Text("Snoop Dogg A");
		ImGui::SliderFloat("X Translation A", &m_TranslationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat("Y Translation A", &m_TranslationA.y, 0.0f, 540.0f);
		ImGui::SliderFloat("X Scale A", &m_ScaleA.x, 0.1f, 10.0f);
		ImGui::SliderFloat("Y Scale A", &m_ScaleA.y, 0.1f, 10.0f);

		ImGui::Text("Snoop Dogg B");
		ImGui::SliderFloat("X Translation B", &m_TranslationB.x, 0.0f, 960.0f);
		ImGui::SliderFloat("Y Translation B", &m_TranslationB.y, 0.0f, 540.0f);
		ImGui::SliderFloat("X Scale B", &m_ScaleB.x, 0.1f, 10.0f);
		ImGui::SliderFloat("Y Scale B", &m_ScaleB.y, 0.1f, 10.0f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
