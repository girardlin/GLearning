#include "Test3DCube.h"

#include "imgui.h"

namespace test {

	Test3DCube::Test3DCube()
		: m_Vertices{   //positions	   //textures
						-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
						 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
						 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
						 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
						-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
						-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

						-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
						 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
						 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
						 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
						-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
						-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

						-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
						-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
						-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
						-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
						-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
						-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

						 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
						 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
						 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
						 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
						 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
						 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

						-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
						 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
						 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
						 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
						-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
						-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

						-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
						 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
						 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
						 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
						-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
						-0.5f,  0.5f, -0.5f,  0.0f, 1.0f }
	{
		m_ProjectionMatrix = glm::mat4(1.0f);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ModelMatrix = glm::mat4(1.0f);

		m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
		m_Rotation = glm::vec3(0.5f, 1.0f, 0.001f);
		m_Translation = glm::vec3(0.0f, 0.0f, 0.0f);

		/* VAO VBO setup */
		m_VertexBuffer = new VertexBuffer(m_Vertices, 5 * 6 * 6 * sizeof(float));

		m_VertexBufferLayout = new VertexBufferLayout();
		m_VertexBufferLayout->Push<float>(3);
		m_VertexBufferLayout->Push<float>(2);

		m_VertexArray = new VertexArray();
		m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);

		/* Shader setup */
		m_Shader = new Shader("res/shaders/BasicMVP.shader");

		m_Texture = new Texture("res/textures/snoop.jpg");
		m_Texture->Bind();
		m_Shader->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);

		/* Renderer setup */
		m_Renderer = new Renderer();
	}

	Test3DCube::~Test3DCube()
	{
		m_VertexBuffer->Unbind();
		m_VertexArray->Unbind();
		m_Shader->Unbind();
		m_Texture->Unbind();

		delete m_VertexBuffer;
		delete m_VertexBufferLayout;
		delete m_VertexArray;
		delete m_Shader;
		delete m_Texture;
		delete m_Renderer;

		glDisable(GL_DEPTH_TEST);
	}

	void Test3DCube::OnUpdate(float deltaTime)
	{

	}

	void Test3DCube::OnRender()
	{
		//Cube
		{
			glClearColor(0.0f, 0.7f, 0.2f, 1.0f);

			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_ProjectionMatrix = glm::mat4(1.0f);
			m_ViewMatrix = glm::mat4(1.0f);
			m_ModelMatrix = glm::mat4(1.0f);

			m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f);
			m_ViewMatrix = glm::translate(m_ViewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));

			m_ModelMatrix = glm::translate(m_ModelMatrix, m_Translation);
			m_ModelMatrix = glm::rotate(m_ModelMatrix, (float)glfwGetTime() * glm::radians(50.0f), m_Rotation);
			m_ModelMatrix = glm::scale(m_ModelMatrix, m_Scale);
	
			glm::mat4 mvp = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	void Test3DCube::OnImGuiRender()
	{
		ImGui::Text("Cube");
		ImGui::SliderFloat3("Translation", &m_Translation.x, -2.0f, 2.0f);
		ImGui::SliderFloat3("Rotation", &m_Rotation.x, 0.001f, 1.0f);
		ImGui::SliderFloat3("Scale", &m_Scale.x, 0.001f, 1.0f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
