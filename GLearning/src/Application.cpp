#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Renderer.h"
#include "Window.h"

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

#include "tests/2D/TestClearColor.h"
#include "tests/2D/TestTriangle.h"
#include "tests/2D/TestTexture.h"
#include "tests/2D/Test2DTransform.h"
#include "tests/3D/Test3DCube.h"
#include "tests/3D/Test3DMultiCube.h"
#include "tests/3D/Test3DMultiCubeCamera.h"
#include "tests/3D/Test3DFreeCamera.h"
#include "tests/3D/TestLighting.h"
#include "tests/3D/TestMaterial.h"

void ProcessGeneralInputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

static float G_DeltaTime = 0.0f;
static float G_LastFrame = 0.0f;

int main(void)
{
	Window window("OpenGL Testing Environment", 1600, 900);
	{
		/* instantiate renderer */
		Renderer renderer;

		/* imgui context creation and intialization */
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window.GetWindow(), true);
		ImGui::StyleColorsDark();

		/* test framework setup */
		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;

		/* test registration */
		testMenu->RegisterTest<test::TestClearColor>("Clear Color");
		testMenu->RegisterTest<test::TestTriangle>("Triangle");
		testMenu->RegisterTest<test::TestTexture>("Texture");
		testMenu->RegisterTest<test::Test2DTransform>("2D Transform");
		testMenu->RegisterTest<test::Test3DCube>("3D Cube");
		testMenu->RegisterTest<test::Test3DMultiCube>("3D Multiple Cubes");
		testMenu->RegisterTest<test::Test3DMultiCubeCamera>("3D Multiple Cubes with Camera");
		testMenu->RegisterTest<test::Test3DFreeCamera>("3D Free Camera Test");
		testMenu->RegisterTest<test::TestLighting>("Lighting");
		testMenu->RegisterTest<test::TestMaterial>("Materials");
		
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window.GetWindow()))
		{
			/* deltaTime calculation */
			float currentFrame = glfwGetTime();
			G_DeltaTime = currentFrame - G_LastFrame;
			G_LastFrame = currentFrame;

			/* Render loop */
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			renderer.Clear();

			/* imgui frame creation */
			ImGui_ImplGlfwGL3_NewFrame();

			if (currentTest)
			{
				ProcessGeneralInputs(window.GetWindow());
				currentTest->OnUpdate(G_DeltaTime);
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

			/* swap buffers and poll events */
			window.Update();
		}
		delete testMenu;
	}
	/* cleanup */
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}