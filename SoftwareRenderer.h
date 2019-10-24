#pragma once
#include "MathLib4D.h"
#include "TextureResource.h"
#include <functional>

typedef unsigned char Rgb[3];

struct Vertex {
	Vertex() {}

	Vertex(Vector2 inVector)
	{
		position = inVector;
	}

	Vector2 position;		//Positions
	Vector2 uv;			//Texturecoordinates
	//float u, v;			//Texturecoordinates
	float n0, n1, n2;	//Normals
};

struct Triangle {
	Triangle(Vertex v0, Vertex v1, Vertex v2)
	{
		this->v0 = v0;
		this->v1 = v1;
		this->v2 = v2;
	}
	Vertex v0, v1, v2;
};

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
	//int squareSize = 10;
	int squareSize = 200;
	int imageWidth = squareSize;
	int imageHeight = squareSize;
	std::vector<Triangle> triangles;

	FILE* filePtr;

	SoftwareRenderer();
	~SoftwareRenderer();
	void SoftwareRenderer::DrawTriangle(Vector2 v0, Vector2 v1, Vector2 v2);
	void SoftwareRenderer::DrawFlatTopTriangle(Vector2 v0, Vector2 v1, Vector2 v2);
	void SoftwareRenderer::DrawFlatBotTriangle(Vector2 v0, Vector2 v1, Vector2 v2);
	std::function<void(int xCoord, int yCoord, Rgb* fetchTexture, Rgb* rasterizedTexture, Triangle triangle)> functionLamda;
	Rgb* SoftwareRenderer::FetchDataFromTexture(const char* path);
	float SoftwareRenderer::EdgeFunction(Vector2 a, Vector2 b, Vector2 c);
	void SoftwareRenderer::Init();
	void SoftwareRenderer::Start();
	void SoftwareRenderer::Shutdown();
	bool SoftwareRenderer::PointInTriangle(Vector2 A, Vector2 B, Vector2 C, Vector2 point);
	//void SoftwareRenderer::DrawFlatTopTriangle(const Vector2& v0, const Vector2& v1, const Vector2& v2);
	//void SoftwareRenderer::DrawFlatBotTriangle(const Vector2& v0, const Vector2& v1, const Vector2& v2);
};

