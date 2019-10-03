#pragma once
#include "MathLib4D.h"
#include "TextureResource.h"

class SoftwareRenderer
{
public:

	float* vertexBuffer;
	unsigned int* indexBuffer;
	MatrixLib4D mvpMatrix;
	TextureResource texture;


	SoftwareRenderer();
	~SoftwareRenderer();

	
};

