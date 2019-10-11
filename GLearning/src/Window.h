#pragma once

#include "Renderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

class Window
{
private:
	GLFWwindow* m_Window;
	const char* m_WindowName;
	float m_Width;
	float m_Height;

public:
	Window(const char* windowName, const float& width, const float& height)
		: m_Window(nullptr), m_WindowName(windowName), m_Width(width), m_Height(height)
	{
		/* Initialize the library */
		if (!glfwInit())
		{
			std::cout << "Failed to intialize GLFW" << std::endl;
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Create a windowed mode window and its OpenGL context */
		m_Window = glfwCreateWindow(m_Width, m_Height, m_WindowName, NULL, NULL);
		if (!m_Window)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}

		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

		/* Make the window's context current */
		glfwMakeContextCurrent(m_Window);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "GLEW Initialization Error" << std::endl;
		}

		std::cout << glGetString(GL_VERSION) << std::endl;

		/* v-sync and blending enabled */
		glfwSwapInterval(1);
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		/* wireframe mode */
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	~Window()
	{

	}

	void Update()
	{
		/* Swap front and back buffers */
		glfwSwapBuffers(m_Window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	inline GLFWwindow* GetWindow() { return m_Window; }
};
