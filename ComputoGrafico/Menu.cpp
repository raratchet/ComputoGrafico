#include "Menu.h"
#include<iostream>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>


Menu::Menu()
{

}

Menu::~Menu()
{
}

void Menu::Init()
{
	std::cout << " Menu Init" << std::endl;
	this->platform = Platform::GetPtr();
	this->manager = GameStateManager::getPtr();
	camera = Camera(glm::vec3(0, 0, 0.6f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 55.0f, 0.1f);
	shaderManager = ShaderManager::getPtr();
	shaderManager->initShader(&camera);
	shaderManager->LoadShaders("OneColor", "Assets/Shaders/OneColor.vert", "Assets/Shaders/OneColor.frag");
	LoadModels();
	
}

void Menu::LoadModels()
{
	unsigned int indices[] = {
	0,1,2,
	0,3,2
	};

	GLfloat vertices[] = {
	0.0f, 0.0f,0.0f,
	0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 0.0f, 0.0f
	};

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 6);
	meshList.push_back(obj1);
}
void Menu::LoadShaders()
{
	
}

void Menu::Draw()
{
	platform->RenderClear();
	shaderManager->Activate("OneColor");
	shaderManager->draw();
	glm::mat4 model(1);
	GLint uniformModel = shaderManager->GetModelLocation();
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	meshList[0]->RenderMesh();
	platform->RenderPresent();
}
bool Menu::MouseInput(int x, int y, bool leftbutton)
{
	if (x != -1 || y != -1)
		camera.mouseControl(x, y);

	return false;
}

bool Menu::Input(std::map<int, bool> keys)
{
	camera.keyControl(keys, platform->GetDeltaTime());
	return false;
}


void Menu::Update()
{
}

void Menu::Close()
{
	std::cout << " Close Init" << std::endl;
}