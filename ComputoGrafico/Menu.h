#pragma once
#include "BCE/GameState.h"
#include "BCE/GameStateManager.h"
#include "BCE/Mesh.h"
#include "BCE/Shader.h"
#include<vector>
class Menu : public GameState
{
private:
	Platform* platform;
	GameStateManager* manager;

	std::vector<Mesh*> meshList;
	std::vector<Shader> shaderList;

	const char* vShader = "Assets/Shaders/Menu/shader.vert";

	// Fragment Shader
	const char* fShader = "Assets/Shaders/Menu/shader.frag";
public:
	Menu();
	~Menu();
	void Init(Platform* platform, GameStateManager* manager) override;
	void Draw() override;
	bool Input(int keyInput) override;
	void Update() override;
	void Close() override;
	void LoadShaders();
	void LoadModels();
};