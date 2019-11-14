#include "TestMaterial.h"

#include "imgui.h"

namespace test {

	TestMaterial::TestMaterial() :
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
						-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f }
	{
		/* Multipliers */
		m_OrbitRadius = 1.0f;
		m_RotationSpeed = 1.0f;
		m_FOV = 45.0f;

		m_ProjectionMatrix = glm::mat4(1.0f);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ModelMatrix = glm::mat4(1.0f);
		m_NormalMatrix = glm::mat3(1.0f);

		m_LightPosition = glm::vec3(1.0f, 0.0f, 0.0f);

		/* Object properties */
		m_Scale = glm::vec3(0.5f, 0.5f, 0.5f);
		m_Rotation = glm::vec3(1.0f, 1.0f, 1.0f);
		m_Translation = glm::vec3(0.0f, 0.0f, 0.0f);

		/* Light Color */
		m_LightColor = glm::vec3(1.0f);

		/* VBO and layout setup */
		m_VertexBuffer = new VertexBuffer(m_Vertices, 8 * 6 * 6 * sizeof(float));

		m_VertexBufferLayout = new VertexBufferLayout();
		m_VertexBufferLayout->Push<float>(3);
		m_VertexBufferLayout->Push<float>(2);
		m_VertexBufferLayout->Push<float>(3);

		/* Non-lamp object VAO setup */
		m_ObjectVertexArray = new VertexArray();
		m_ObjectVertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);

		/* Lamp object VAO setup */
		m_LampVertexArray = new VertexArray();
		m_LampVertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);

		/* Non-lamp object diffuse, specular, and shader setup */
		m_ObjectDiffuse = new Texture("res/textures/container.png");
		m_ObjectSpecular = new Texture("res/textures/container_specular.png");

		m_ObjectShader = new Shader("res/shaders/MaterialLighting.shader");
		m_ObjectShader->Bind();
		m_ObjectShader->SetUniform1i("u_Material.diffuseColor", 0);
		m_ObjectShader->SetUniform1i("u_Material.specularColor", 1);
		m_ObjectShader->SetUniform3f("u_LightColor", 1.0f, 1.0f, 1.0f);

		/* Lamp Object Texture & Shader setup */
		m_LampTexture = new Texture("res/textures/lamp.jpg");

		m_LampShader = new Shader("res/shaders/BasicLamp.shader");
		m_LampShader->Bind();
		m_LampShader->SetUniform1i("u_Material.diffuseColor", 0);

		/* Camera setup */
		m_Camera = new Camera();
		InputManager::BindCamera(m_Camera);
	}

	TestMaterial::~TestMaterial()
	{
		m_VertexBuffer->Unbind();
		m_ObjectVertexArray->Unbind();
		m_LampVertexArray->Unbind();
		m_ObjectShader->Unbind();
		m_LampShader->Unbind();
		m_ObjectDiffuse->Unbind();
		m_ObjectSpecular->Unbind();
		m_LampTexture->Unbind();

		delete m_VertexBuffer;
		delete m_VertexBufferLayout;
		delete m_ObjectVertexArray;
		delete m_LampVertexArray;
		delete m_ObjectShader;
		delete m_LampShader;
		delete m_ObjectDiffuse;
		delete m_ObjectSpecular;
		delete m_LampTexture;
		delete m_Camera;

		GLCall(glDisable(GL_DEPTH_TEST));
		GLCall(glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL));

		InputManager::UnbindCamera();
	}

	void TestMaterial::OnUpdate(float deltaTime)
	{
		/* Inputs */
		InputManager::ProcessInputs(deltaTime);
	}

	void TestMaterial::OnRender()
	{
		/* Object and Lamp */
		{
			GLCall(glClearColor(0.05f, 0.05f, 0.05f, 1.0f));

			GLCall(glEnable(GL_DEPTH_TEST));
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

			m_ProjectionMatrix = glm::mat4(1.0f);
			m_ViewMatrix = glm::mat4(1.0f);
			m_ModelMatrix = glm::mat4(1.0f);

			float LightPositionX = float(sin(glfwGetTime()) * m_OrbitRadius);
			float LightPositionY = float(sin(glfwGetTime() * 2) * m_OrbitRadius * 0.75f);
			float LightPositionZ = float(cos(glfwGetTime()) * m_OrbitRadius);

			m_LightPosition = glm::vec3(LightPositionX, LightPositionY, LightPositionZ);

			/* Set values for VP matrices */
			m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), 16.0f / 9.0f, 0.1f, 100.0f);

			m_ViewMatrix = m_Camera->GetViewMatrix();

			// Object Render
			/* Model Matrix*/
			m_ModelMatrix = glm::translate(m_ModelMatrix, m_Translation);
			m_ModelMatrix = glm::rotate(m_ModelMatrix, (float)glfwGetTime() * glm::radians(m_RotationSpeed * 20.0f), m_Rotation);
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

			//Fragment Uniforms
			m_ObjectShader->SetUniform1f("u_Material.shininess", 256.0f);

			m_ObjectShader->SetUniform3f("u_Light.ambientColor", 0.2f, 0.2f, 0.2f);
			m_ObjectShader->SetUniform3f("u_Light.diffuseColor", m_LightColor);
			m_ObjectShader->SetUniform3f("u_Light.specularColor", 1.0f, 1.0f, 1.0f);
			m_ObjectShader->SetUniform3f("u_Light.position", m_LightPosition);

			m_ObjectShader->SetUniform3f("u_ViewPosition", m_Camera->GetCameraPosition());

			/* Draw Call for Object*/
			m_ObjectVertexArray->Bind();

			m_ObjectDiffuse->Bind(0);
			m_ObjectSpecular->Bind(1);

			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

			// Lamp Render
			/* Model Matrix */
			m_ModelMatrix = glm::mat4(1.0f);
			m_ModelMatrix = glm::translate(m_ModelMatrix, m_LightPosition);
			m_ModelMatrix = glm::rotate(m_ModelMatrix, (float)glfwGetTime(), glm::vec3(1.0f));
			m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(0.3f));

			/* Matrix multiplication on CPU and set uniforms to send transform and lighting info to shader */
			MVP = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
			m_LampShader->Bind();
			m_LampShader->SetUniformMat4f("u_MVP", MVP);
			m_LampShader->SetUniform3f("u_LightColor", m_LightColor);

			/* Draw Call for Light Source */
			m_LampVertexArray->Bind();

			m_LampTexture->Bind(0);

			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		}
	}

	void TestMaterial::OnImGuiRender()
	{
		ImGui::Text("Lighting Test - Camera Implemented");

		ImGui::SliderFloat3("Object Scale", &m_Scale.x, 0.001f, 1.0f);
		ImGui::ColorEdit3("Light Color", &m_LightColor.r);
		ImGui::NewLine();

		ImGui::SliderFloat("Object Rotation Speed", &m_RotationSpeed, 0.01f, 10.0f);
		ImGui::SliderFloat("Light Orbit Radius", &m_OrbitRadius, 1.0f, 2.0f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
