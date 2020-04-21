#include "Platform.h"
#include <iostream>


Platform::Platform(std::string name)
{
	width = 800;
	height = 600;
	this->name = name;
	init();
}

void Platform::init()
{
	if (!glfwInit())
	{
		std::cout<<"Error Initialising GLFW";
		glfwTerminate();
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (!mainWindow)
	{
		printf("Error creating GLFW window!");
		glfwTerminate();
		return;
	}

	// Get buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set the current context
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension access
	glewExperimental = GL_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		printf("Error: %s", glewGetErrorString(error));
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return;
	}

	glEnable(GL_DEPTH_TEST);

	// Create Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
}
Platform::~Platform()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

void Platform::RenderClear()
{
	// Clear the window
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Platform::RenderPresent()
{
	glfwSwapBuffers(mainWindow);
}

void Platform::CheckEvent(GameState* obj, bool (GameState::* f)(int))
{
	glfwPollEvents();
}
int Platform::GetWidth()
{
	return width;
}

int Platform::GetHeight()
{
	return height;
}