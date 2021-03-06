#include "Menu.h"
#include<iostream>
#include <glm.hpp>
#include <time.h>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

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
	this->manager = GameStateManager::GetPtr();
	camera = Camera(glm::vec3(0, 0, 0.6f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 55.0f, 0.1f);
	shaderManager = ShaderManager::getPtr();
	shaderManager->initShader(&camera);
	shaderManager->LoadShaders("OneColor", "Assets/Shaders/OneColor.vert", "Assets/Shaders/OneColor.frag");
	shaderManager->LoadShaders("gouraud-shader", "Assets/Shaders/gouraud-shader.vert", "Assets/Shaders/gouraud-shader.frag");
	shaderManager->LoadShaders("phong-shader", "Assets/Shaders/phong-shader.vert", "Assets/Shaders/phong-shader.frag");
	shaderManager->LoadShaders("toon-shader", "Assets/Shaders/toon-shader.vert", "Assets/Shaders/toon-shader.frag");
		
	LoadModels();
	weapon = new Model();
	weapon->LoadModel("Assets/Models/pina_pose.obj");
	weapon->AddTexture("pina.png");
	weapon->AddTexture("pina_normal.png");

	srand(time(NULL));
	angle = 0;

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Assets/Textures/Skybox/cupertin-lake_ft.tga");
	skybox = new Skybox(skyboxFaces);
}

void Menu::LoadModels()
{
	unsigned int indices[] = {
				0,1,2,
				1,2,3,
	};

	GLfloat vertices[] = {
		// floor
		-1.0, -1.0,  -1.0, 0.0f, 0.0f,		0.0f, 0.0f, 0.8f,1.0f, 0.0f, 0.0f,//0
		-1.0, -1.0,  1.0,0.0f, 1.0f,		0.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,//1
		1.0,  -1.0,  -1.0,1.0f, 0.0f,		0.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,//2
		1.0,  -1.0,  1.0,1.0f, 1.0f,		0.0f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,//3
	};
	calcAverageNormals(indices, 6, vertices, 44, 11, 5);
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 44, 6, 11);
	meshList.push_back(obj1);

	mainTexture = new Texture("Assets/Textures/MultiTexture/mainTexture.png");
	mainTexture->LoadTexture();
	rTexture = new Texture("Assets/Textures/MultiTexture/rTexture.png");
	rTexture->LoadTexture();
	gTexture = new Texture("Assets/Textures/MultiTexture/gTexture.png");
	gTexture->LoadTexture();
	bTexture = new Texture("Assets/Textures/MultiTexture/bTexture.png");
	bTexture->LoadTexture();
	blendTexture = new Texture("Assets/Textures/MultiTexture/blendTexture.png");
	blendTexture->LoadTexture();
	normalTexture = new Texture("Assets/Textures/MultiTexture/bricknormal.png");
	normalTexture->LoadTexture();
}
void Menu::LoadShaders()
{
	
}

void Menu::Draw()
{
	platform->RenderClear();
	skybox->Draw(shaderManager->GetViewMatrix(), shaderManager->GetProjectionMatrix());

	shaderManager->Activate("phong-shader");
	shaderManager->draw();
	glm::mat4 model(1);
	GLint uniformModel = shaderManager->GetModelLocation();
	model = glm::translate(model, glm::vec3(0.0f, -10.0f, -2.5f));
	model = glm::scale(model, glm::vec3(100.0f, 10.0f, 100.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	mainTexture->UseTexture(GL_TEXTURE0);
	rTexture->UseTexture(GL_TEXTURE1);
	gTexture->UseTexture(GL_TEXTURE2);
	bTexture->UseTexture(GL_TEXTURE3);
	blendTexture->UseTexture(GL_TEXTURE4);
	normalTexture->UseTexture(GL_TEXTURE5);

	glUniform1i(shaderManager->GetmainTex(), 0);
	glUniform1i(shaderManager->GetrTex(), 1);
	glUniform1i(shaderManager->GetgTex(), 2);
	glUniform1i(shaderManager->GetbTex(), 3);
	glUniform1i(shaderManager->GetblendTexture(), 4);
	glUniform1i(shaderManager->GetNormalTexture(), 5);


	meshList[0]->RenderMesh();

	//
	//shaderManager->Activate("phong-shader");
	//shaderManager->draw();
	//uniformModel = shaderManager->GetModelLocation();
	//GLint color1 = shaderManager->GetColor1();
	//GLint color2 = shaderManager->GetColor2();
	//model = glm::translate(model, glm::vec3(10.0f, 0.0f, -8.5f));
	//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
	//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	//glUniform3f(color1, 0, angle, 0.0f );
	//angle = angle + 1.0f;
	//glUniform3f(color2, 0.0f, 0.0f, 1.0f);

	//meshList[0]->RenderMesh();

	shaderManager->Activate("phong-shader");
	shaderManager->draw();
	transform.SetTranslation(0.0f, 0.0f, 0.0f);
	transform.SetScale(1.1f, 1.1f, 1.11f);
	transform.SetRotation(0, 0, 0);
	weapon->SetTransform(&transform);
	weapon->Draw();
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