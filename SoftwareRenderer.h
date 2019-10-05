#pragma once
#include "MathLib4D.h"
#include "TextureResource.h"
#include <functional>

typedef unsigned char Rgb[3];


class SoftwareRenderer
{
public:

	struct Color 
	{
		unsigned char color[3];
	};

	float* vertexBuffer;
	unsigned int* indexBuffer;
	MatrixLib4D mvpMatrix;
	TextureResource texture;

	//unsigned char* fetchTexture[3];
	//unsigned char* rasterizeTexture[3];	
	Rgb* fetchTexture;
	Rgb* rasterizeTexture;
	//Rgb* fetchTexture[5*5];
	//Rgb* rasterizeTexture[5*5];
	int imageWidth = 5;
	int imageHeight = 5;

	FILE* filePtr;

	SoftwareRenderer();
	~SoftwareRenderer();
	void SoftwareRenderer::DrawTriangle(Vector2 v0, Vector2 v1, Vector2 v2);
	void SoftwareRenderer::DrawFlatTopTriangle(Vector2 v0, Vector2 v1, Vector2 v2);
	void SoftwareRenderer::DrawFlatBotTriangle(Vector2 v0, Vector2 v1, Vector2 v2);
	std::function<void(int xCoord, int yCoord, Rgb* fetchTexture, Rgb* rasterizedTexture)> functionLamda;
	Rgb* SoftwareRenderer::FetchDataFromTexture(const char* path);
	float SoftwareRenderer::EdgeFunction(Vector2 a, Vector2 b, Vector2 c);
	void SoftwareRenderer::Init();
	void SoftwareRenderer::Shutdown();
	//void SoftwareRenderer::DrawFlatTopTriangle(const Vector2& v0, const Vector2& v1, const Vector2& v2);
	//void SoftwareRenderer::DrawFlatBotTriangle(const Vector2& v0, const Vector2& v1, const Vector2& v2);
};

