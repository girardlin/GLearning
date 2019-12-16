#include "TestDirectionalLighting.h"

#include "imgui.h"

namespace test {

	TestDirectionalLighting::TestDirectionalLighting() :
		m_Vertices{		 //positions	      //textures    //normals
						-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.0f, -1.0f,
						 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, -1.0f,
						 0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,
						 0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,
						-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, -1.0f,
						-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.0f, -1.0f,

						-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,
						 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
						 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
						 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
						-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
						-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,

						-0.5f,  0.5f,  0.5f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f,
						-0.5f,  0.5f, -0.5f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
						-0.5f, -0.5f, -0.5f,  0.0f,  1.0f, -1.0f,  0.0f,  0.0f,
						-0.5f, -0.5f, -0.5f,  0.0f,  1.0f, -1.0f,  0.0f,  0.0f,
						-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
						-0.5f,  0.5f,  0.5f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f,

						 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,
						 0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
						 0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,
						 0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,
						 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
						 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,

						-0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f, -1.0f,  0.0f,
						 0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
						 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f,
						 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f,
						-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f, -1.0f,  0.0f,
						-0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f, -1.0f,  0.0f,

						-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
						 0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
						 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
						 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
						-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
						-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f },
		m_CubePositions{
						glm::vec3(0.0f,  0.0f,  0.0f),
						glm::vec3(2.0f,  5.0f, -15.0f),
						glm::vec3(-1.5f, -2.2f, -2.5f),
						glm::vec3(-3.8f, -2.0f, -12.3f),
						glm::vec3(2.4f, -0.4f, -3.5f),
						glm::vec3(-1.7f,  3.0f, -7.5f),
						glm::vec3(1.3f, -2.0f, -2.5f),
						glm::vec3(1.5f,  2.0f, -2.5f),
						glm::vec3(1.5f,  0.2f, -1.5f),
						glm::vec3(-1.3f,  1.0f, -1.5f) }
	{
		/* Multipliers */
		m_RotationSpeed = 1.0f;
		m_FOV = 45.0f;

		m_ProjectionMatrix = glm::mat4(1.0f);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ModelMatrix = glm::mat4(1.0f);
		m_NormalMatrix = glm::mat3(1.0f);

		/* Object properties */
		m_Scale = glm::vec3(0.5f, 0.5f, 0.5f);
		m_Rotation = glm::vec3(1.0f, 1.0f, 1.0f);
		m_Translation = glm::vec3(0.0f, 0.0f, 0.0f);

		/* Light Color & Direction */
		m_LightColor = glm::vec3(1.0f);
		m_LightDirection = glm::vec3(0.2f, 1.0f, 0.3f);

		/* VBO and layout setup */
		m_VertexBuffer = new VertexBuffer(m_Vertices, 8 * 6 * 6 * sizeof(float));

		m_VertexBufferLayout = new VertexBufferLayout();
		m_VertexBufferLayout->Push<float>(3);
		m_VertexBufferLayout->Push<float>(2);
		m_VertexBufferLayout->Push<float>(3);

		/* Object VAO setup */
		m_ObjectVertexArray = new VertexArray();
		m_ObjectVertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);


		/* Object diffuse, specular, and shader setup */
		m_ObjectDiffuse = new Texture("res/textures/container.png");
		m_ObjectSpecular = new Texture("res/textures/container_specular.png");

		m_ObjectDiffuse->Bind(0);
		m_ObjectSpecular->Bind(1);

		m_ObjectShader = new Shader("res/shaders/DirectionalLighting.shader");
		m_ObjectShader->Bind();
		m_ObjectShader->SetUniform1i("u_Material.diffuseColor", 0);
		m_ObjectShader->SetUniform1i("u_Material.specularColor", 1);
		m_ObjectShader->SetUniform1f("u_Material.shininess", 256.0f);

		m_ObjectShader->SetUniform3f("u_LightColor", 1.0f, 1.0f, 1.0f);

		/* Camera setup */
		m_Camera = new Camera();
		InputManager::BindCamera(m_Camera);
	}

	TestDirectionalLighting::~TestDirectionalLighting()
	{
		m_VertexBuffer->Unbind();
		m_ObjectVertexArray->Unbind();
		m_ObjectShader->Unbind();
		m_ObjectDiffuse->Unbind();
		m_ObjectSpecular->Unbind();

		delete m_VertexBuffer;
		delete m_VertexBufferLayout;
		delete m_ObjectVertexArray;
		delete m_ObjectShader;
		delete m_ObjectDiffuse;
		delete m_ObjectSpecular;
		delete m_Camera;

		GLCall(glDisable(GL_DEPTH_TEST));
		GLCall(glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL));

		InputManager::UnbindCamera();
	}

	void TestDirectionalLighting::OnUpdate(float deltaTime)
	{
		/* Inputs */
		InputManager::ProcessInputs(deltaTime);
	}

	void TestDirectionalLighting::OnRender()
	{
		/* Object */
		{
			GLCall(glClearColor(0.05f, 0.05f, 0.05f, 1.0f));

			GLCall(glEnable(GL_DEPTH_TEST));
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

			m_ProjectionMatrix = glm::mat4(1.0f);
			m_ViewMatrix = glm::mat4(1.0f);
			m_ModelMatrix = glm::mat4(1.0f);

			/* Set values for VP matrices */
			m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), 16.0f / 9.0f, 0.1f, 100.0f);

			m_ViewMatrix = m_Camera->GetViewMatrix();

			// Object Render
			//Fragment Uniforms
			m_ObjectShader->SetUniform3f("u_Light.ambientColor", 0.2f, 0.2f, 0.2f);
			m_ObjectShader->SetUniform3f("u_Light.diffuseColor", m_LightColor);
			m_ObjectShader->SetUniform3f("u_Light.specularColor", 1.0f, 1.0f, 1.0f);
			m_ObjectShader->SetUniform3f("u_Light.direction", -m_LightDirection.x, -m_LightDirection.y, -m_LightDirection.z);

			m_ObjectShader->SetUniform3f("u_ViewPosition", m_Camera->GetCameraPosition());

			for (unsigned int i = 0; i < 10; i++)
			{
				/* Model Matrix*/
				m_ModelMatrix = glm::mat4(1.0f);
				m_ModelMatrix = glm::translate(m_ModelMatrix, m_CubePositions[i]);
				m_ModelMatrix = glm::rotate(m_ModelMatrix, (float)glfwGetTime() * glm::radians(m_RotationSpeed * 20.0f * i), m_Rotation);
				m_ModelMatrix = glm::scale(m_ModelMatrix, m_Scale);

				/* Normal Matrix */
				m_NormalMatrix = glm::mat3(glm::transpose(glm::inverse(m_ModelMatrix)));

				/* Matrix multiplication on CPU and set uniforms to send transform and lighting info to object shader */
				glm::mat4 MVP = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;

				m_ObjectShader->Bind();

				//Vertex Uniforms
				m_ObjectShader->SetUniformMat4f("u_ModelMatrix", m_ModelMatrix);
				m_ObjectShader->SetUniformMat3f("u_NormalMatrix", m_NormalMatrix);
				m_ObjectShader->SetUniformMat4f("u_MVP", MVP);

				/* Draw Call for Object*/
				m_ObjectVertexArray->Bind();

				GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			}
		}
	}

	void TestDirectionalLighting::OnImGuiRender()
	{
		ImGui::Text("Lighting Test - Camera Implemented");

		ImGui::SliderFloat3("Object Scale", &m_Scale.x, 0.001f, 1.0f);
		ImGui::SliderFloat3("Light Direction", &m_LightDirection.x, 0.001f, 1.0f);
		ImGui::ColorEdit3("Light Color", &m_LightColor.r);
		ImGui::NewLine();

		ImGui::SliderFloat("Object Rotation Speed", &m_RotationSpeed, 0.01f, 10.0f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
