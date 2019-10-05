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
	void SoftwareRenderer::DrawTriangle(Vector2 v0, Vector2 v1, Vector2 v2);
	void SoftwareRenderer::DrawFlatTopTriangle(Vector2 v0, Vector2 v1, Vector2 v2);
	void SoftwareRenderer::DrawFlatBotTriangle(Vector2 v0, Vector2 v1, Vector2 v2);
	//void SoftwareRenderer::DrawFlatTopTriangle(const Vector2& v0, const Vector2& v1, const Vector2& v2);
	//void SoftwareRenderer::DrawFlatBotTriangle(const Vector2& v0, const Vector2& v1, const Vector2& v2);
};

