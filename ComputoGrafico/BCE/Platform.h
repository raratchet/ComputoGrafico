#pragma once
#include <string>
#include "GameState.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class GameState;

class Platform
{
private:
	int width;
	int height;
	std::string name;

	GLFWwindow* mainWindow;
	GLint bufferWidth, bufferHeight;
private:
	void init();
public:
	Platform(std::string name);
	~Platform();
	void RenderClear();
	void RenderPresent();
	void CheckEvent(GameState* obj, bool (GameState::* f)(int));
	int GetWidth();
	int GetHeight();

};