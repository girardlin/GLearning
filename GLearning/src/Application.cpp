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

#include "tests/TestClearColor.h"
#include "tests/TestTriangle.h"
#include "tests/TestTexture.h"
#include "tests/Test2DTransform.h"
#include "tests/Test3DCube.h"
#include "tests/Test3DMultiCube.h"

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

	/* v-sync and blending enabled */
	glfwSwapInterval(1);
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	{
		/* instantiate renderer */
		Renderer renderer;

		/* imgui context creation and intialization */
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;

		testMenu->RegisterTest<test::TestClearColor>("Clear Color");
		testMenu->RegisterTest<test::TestTexture>("Texture");
		testMenu->RegisterTest<test::TestTriangle>("Triangle");
		testMenu->RegisterTest<test::Test2DTransform>("2D Transform");
		testMenu->RegisterTest<test::Test3DCube>("3D Cube");
		testMenu->RegisterTest<test::Test3DMultiCube>("3D Multiple Cubes");
		

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render loop */
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			renderer.Clear();

			/* imgui frame creation */
			ImGui_ImplGlfwGL3_NewFrame();
			if (currentTest)
			{
				currentTest->OnUpdate(0.0f);
				currentTest->OnRender();
				ImGui::Begin("Test Menu");
				if (currentTest != testMenu && ImGui::Button("<--- Back"))
				{
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();
			}

			/* imgui render call */
			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
		delete testMenu;
	}
	/* cleanup */
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}