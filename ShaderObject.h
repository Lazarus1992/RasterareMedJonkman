#pragma once
#include "core/app.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;
class ShaderObject
{
private:
	string output1;
	string output2;
	GLuint vertexShader;
	GLuint pixelShader;

public:
	void LoadFromFile();
	// void LoadShader(const string& fileName);
	void LoadShader(const string& fileNameVS, const string& fileNameFS);
	void SetupShaders(int shaderID);
	void BindShaders();
	void Apply();
	void Matrix4fv(GLuint, float*);
	void Vector4fv(GLuint uniformLocation, float *p);
	GLuint UniformLocation(const GLchar*);
	GLuint program;
	ShaderObject();
	~ShaderObject();

};