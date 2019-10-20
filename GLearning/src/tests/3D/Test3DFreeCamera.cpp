#include "Test3DFreeCamera.h"

#include "imgui.h"

namespace test {

	Test3DFreeCamera::Test3DFreeCamera() :
		m_Vertices{		 //positions	      //textures
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
						-0.5f,  0.5f, -0.5f,  0.0f, 1.0f },
		m_CubePositions{
						 glm::vec3(0.0f,  0.0f,  0.0f),
						 glm::vec3(2.0f,  -2.3f, -3.0f),
						 glm::vec3(-1.5f, -2.2f, -2.5f),
						 glm::vec3(-3.8f, -2.0f, 3.3f),
						 glm::vec3(2.4f, -0.4f, -3.5f),
						 glm::vec3(-1.7f,  3.0f, -5.5f),
						 glm::vec3(1.3f, -2.0f,	2.5f),
						 glm::vec3(1.5f,  2.0f, -2.5f),
						 glm::vec3(1.5f,  -0.2f, -1.5f),
						 glm::vec3(-1.3f,  1.0f, 1.5f) }
	{
		/* multipliers */
		m_RotationSpeed = 1.0f;
		m_FOV = 45.0f;

		m_ProjectionMatrix = glm::mat4(1.0f);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ModelMatrix = glm::mat4(1.0f);

		/* cube properties */
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

		m_Texture = new Texture("res/textures/lamp.jpg");
		m_Texture->Bind();
		m_Shader->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);

		/* Camera setup */
		m_Camera = new Camera();
		InputManager::BindCamera(m_Camera);
	}

	Test3DFreeCamera::~Test3DFreeCamera()
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
		delete m_Camera;

		GLCall(glDisable(GL_DEPTH_TEST));
		GLCall(glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL));

		InputManager::UnbindCamera();
	}

	void Test3DFreeCamera::OnUpdate(float deltaTime)
	{
		/* Inputs */
		InputManager::ProcessInputs(deltaTime);
	}

	void Test3DFreeCamera::OnRender()
	{
		/* Cubes */
		{
			GLCall(glClearColor(0.1f, 0.3f, 0.2f, 1.0f));

			GLCall(glEnable(GL_DEPTH_TEST));
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

			m_ProjectionMatrix = glm::mat4(1.0f);
			m_ViewMatrix = glm::mat4(1.0f);
			m_ModelMatrix = glm::mat4(1.0f);

			/* Set values for MVP matrices */
			m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), 960.0f / 540.0f, 0.1f, 100.0f);

			m_ViewMatrix = m_Camera->GetViewMatrix();

			/* loop to create different model matrices and render multiple cubes */
			for (unsigned int i = 0; i < 10; i++)
			{
				m_ModelMatrix = glm::mat4(1.0f);

				m_ModelMatrix = glm::translate(m_ModelMatrix, m_CubePositions[i]);
				m_ModelMatrix = glm::translate(m_ModelMatrix, m_Translation);
				m_ModelMatrix = glm::rotate(m_ModelMatrix, (float)glfwGetTime() * glm::radians(20.0f * (i + m_RotationSpeed)), m_Rotation);
				m_ModelMatrix = glm::scale(m_ModelMatrix, m_Scale);

				/* Matrix multiplication on CPU and set uniform to send info to shader program */
				glm::mat4 mvp = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
				m_Shader->Bind();
				m_Shader->SetUniformMat4f("u_MVP", mvp);

				GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			}
		}
	}

	void Test3DFreeCamera::OnImGuiRender()
	{
		ImGui::Text("Free Camera Test");
		ImGui::SliderFloat3("Translation", &m_Translation.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("Rotation", &m_Rotation.x, 0.001f, 1.0f);
		ImGui::SliderFloat3("Scale", &m_Scale.x, 0.001f, 2.0f);
		ImGui::SliderFloat("Rotation Speed", &m_RotationSpeed, 0.01f, 10.0f);
		ImGui::SliderFloat("Camera Speed", m_Camera->GetCameraSpeedMultiplierAddress(), 1.0f, 15.0f);
		ImGui::SliderFloat("Field of View / Zoom", &m_FOV, 10.0f, 80.0f);
		ImGui::Text("--> HOLD C TO LOCK CURSOR <--");

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
