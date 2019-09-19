#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();x;ASSERT(GLLogCall(#x, __FILE__, __LINE__))

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(960, 540, "OpenGL Learning Environment", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Initialization Error" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	/* example points */
	float positions[] =
	{
		 -50.0f, -50.0f,  0.0f,  0.0f,  // v1
		  50.0f, -50.0f,  1.0f,  0.0f,  // v2
		  50.0f,  50.0f,  1.0f,  1.0f,  // v3
		 -50.0f,  50.0f,  0.0f,  1.0f   // v4
	};

	/* example ibo */
	unsigned int index[] =
	{
		0, 1, 2, 2, 3, 0
	};

	/* v-sync and blending enabled */
	glfwSwapInterval(1);
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	/* create VAO, create VBO, store data in VBO, setup buffer layout, generate VAO with given VBO and layout defintion */
	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float)); //size of 4 vertices is 4 floats
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	/* create IBO/EBO from example ibo */
	IndexBuffer ib(index, 6);

	/* projection matrix implementation*/
	glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	/* create shader from designated filepath */
	Shader shader("res/shaders/Basic.shader");

	//Initial uniform setter
		//shader.Bind(); 
		//shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		//shader.Unbind(); 

	/* Example texture */
	Texture texture("res/textures/snoop.jpg");
	texture.Bind();
	shader.Bind();
	shader.SetUniform1i("u_Texture", 0);

	va.Unbind();
	ib.Unbind();
	vb.Unbind();

	/* instantiate renderer */
	Renderer renderer;

	/* imgui context creation and intialization */
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	/* tranformation variables */
	glm::vec3 translationA(240, 240, 0);
	glm::vec3 scaleA(1.0, 1.0, 1.0);

	glm::vec3 translationB(720, 240, 0);
	glm::vec3 scaleB(1.0, 1.0, 1.0);

	//color shifting variables
		//float b = 0.0f;
		//float increment = 0.05f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render loop */
		renderer.Clear();

		/* imgui frame creation */
		ImGui_ImplGlfwGL3_NewFrame();

		//color shifting algorithm for uniform
		//shader.SetUniform4f("u_Color", 0.2f, 0.8f, b, 1.0f);
		//if (b > 1.0f) { increment = -0.05f; }
		//else if (b < 0.0f) { increment = 0.05f; }
		//b += increment;

		/* draw calls */
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
			model = glm::scale(model, scaleA);
			glm::mat4 mvp = proj * view * model;
			shader.Bind();
			shader.SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(va, ib, shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
			model = glm::scale(model, scaleB);
			glm::mat4 mvp = proj * view * model;
			shader.Bind();
			shader.SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(va, ib, shader);
		}

		/* IMGUI demo window */
		{
			ImGui::Text("Snoop Dogg A");
			ImGui::SliderFloat("X Translation A", &translationA.x, 0.0f, 960.0f);
			ImGui::SliderFloat("Y Translation A", &translationA.y, 0.0f, 540.0f);
			ImGui::SliderFloat("X Scale A", &scaleA.x, 0.1f, 10.0f);
			ImGui::SliderFloat("Y Scale A", &scaleA.y, 0.1f, 10.0f);

			ImGui::Text("Snoop Dogg B");
			ImGui::SliderFloat("X Translation B", &translationB.x, 0.0f, 960.0f);
			ImGui::SliderFloat("Y Translation B", &translationB.y, 0.0f, 540.0f);
			ImGui::SliderFloat("X Scale B", &scaleB.x, 0.1f, 10.0f);
			ImGui::SliderFloat("Y Scale B", &scaleB.y, 0.1f, 10.0f);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

		/* imgui render call */
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	/* cleanup */
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}