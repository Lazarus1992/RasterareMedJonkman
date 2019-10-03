#pragma once
#include "core/app.h"
#include "string.h"
#include <iostream>

using namespace std;



class TextureResource
{
private:

public:
	GLuint texArray[3];
	// GLuint tex0;
	// GLuint tex1;
	// GLuint tex2;
	GLuint texture;
	TextureResource();
	~TextureResource();
	void Bind(const string& fileName, int textureCount);



};

