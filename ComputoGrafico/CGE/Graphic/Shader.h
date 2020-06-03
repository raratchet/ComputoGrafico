#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetColor1();
	GLuint GetColor2();
	GLuint GetNormalTexture();

	GLuint GetmainTex();
	GLuint GetrTex();
	GLuint GetgTex();
	GLuint GetbTex();
	GLuint GetblendTexture();

	void UseShader();
	void ClearShader();

	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView;
	GLuint color1, color2;
	GLuint myLightPosition;
	GLuint mainTex;
	GLuint rTex;
	GLuint gTex;
	GLuint bTex;
	GLuint blendTexture;
	GLuint normalTexture;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

