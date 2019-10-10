#include "SoftwareRenderer.h"



SoftwareRenderer::SoftwareRenderer()
{
	functionLamda = [this](int xCoord, int yCoord, Rgb* fetchTexture, Rgb* rasterizedTexture, Triangle triangle)
	{
		Triangle localTriangle = triangle; // 0,0		0,5		5,5
		//this->triangles[0]; // 0,0		0,5		5,5
		

		Vector2 vec0 = localTriangle.v0.position;
		Vector2 vec1 = localTriangle.v1.position;
		Vector2 vec2 = localTriangle.v2.position;

		//Vector2 uv0 = localTriangle.v0.uv;
		//Vector2 uv1 = localTriangle.v1.uv;
		//Vector2 uv2 = localTriangle.v2.uv;
		
		cout << "Inside lambda" << endl;

		float area = EdgeFunction(vec0, vec1, vec2);
		//Vector2 p = { (float)xCoord, (float)yCoord }; //USE WITHOUT CENTERPIXEL FOR FETCHING TEXTURE PIXELS
		Vector2 p = { (float)xCoord + 0.5f, (float)yCoord + 0.5f }; //USE WITH	CENTERPIXEL FOR COLORING THE TRIANGLE
		//float w0 = EdgeFunction(vec1, vec2, p);
		//float w1 = EdgeFunction(vec2, vec0, p);
		//float w2 = EdgeFunction(vec0, vec1, p);

		//if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
		if (this->PointInTriangle(vec0, vec1, vec2, p)) {
			//w0 /= area;
			//w1 /= area;
			//w2 /= area;

			//Vector2 textureUV = uv0 * w0 + uv1 * w1 + uv2 * w2;
			//float row = this->imageHeight;
			//float column = this->imageWidth;
			//int pixelToGet = textureUV.y * row * (float)this->imageWidth + textureUV.x * column;

			////Row * width + col
			this->rasterizeTexture[yCoord * this->imageWidth + xCoord][0] = 255;
			this->rasterizeTexture[yCoord * this->imageWidth + xCoord][1] = 1;
			this->rasterizeTexture[yCoord * this->imageWidth + xCoord][2] = 1;

			//this->rasterizeTexture[yCoord * this->imageWidth + xCoord][0] = this->fetchTexture[pixelToGet][0];
			//this->rasterizeTexture[yCoord * this->imageWidth + xCoord][1] = this->fetchTexture[pixelToGet][1];
			//this->rasterizeTexture[yCoord * this->imageWidth + xCoord][2] = this->fetchTexture[pixelToGet][2];
		}

	};

	int x = 1;
	int y = 1;


	//Rgb *data = FetchDataFromTexture("TextureToFetchFrom.ppm");
	this->fetchTexture = FetchDataFromTexture("TextureToFetchFrom.ppm");
	this->rasterizeTexture = new Rgb[this->imageWidth * this->imageHeight];

	
	//FILE *fp = fopen("TextureToFetchFrom.ppm", "wb");

	
	//int* a = new int;
	//functionLamda(x, y, this->fetchTexture, this->rasterizeTexture);




	int stop = 3;
}

SoftwareRenderer::~SoftwareRenderer()
{
}

void SoftwareRenderer::Init(Vector2 v0, Vector2 v1, Vector2 v2)
{
	//Create triangles
	Vertex tempVertex0(v0);
	Vertex tempVertex1(v1);
	Vertex tempVertex2(v2);
	Triangle tempTriangle(tempVertex0, tempVertex1, tempVertex2);
	triangles.push_back(tempTriangle);

	this->filePtr = fopen("TextureToWriteTo.ppm", "wb");
	(void)fprintf(this->filePtr, "P6\n%d %d\n255\n", this->imageHeight, this->imageWidth);
}

void SoftwareRenderer::Shutdown()
{
	(void)fwrite(this->rasterizeTexture, 1, this->imageWidth * this->imageHeight * 3, filePtr);
	(void)fclose(this->filePtr);
}

inline
float SoftwareRenderer::EdgeFunction(Vector2 a, Vector2 b, Vector2 c)
{
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
	//return (c.x - a.x + 0.5f) * (b.y + 0.5f - a.y + 0.5f) - (c.y - a.y + 0.5f) * (b.x + 0.5f  - a.x + 0.5f);
}

bool SoftwareRenderer::PointInTriangle(Vector2 A, Vector2 B, Vector2 C, Vector2 point)
{
	float w1 = (A.x * (C.y - A.y) + (point.y - A.y) * (C.x - A.x) - point.x * (C.y - A.y)) / ((B.y - A.y)*(C.x - A.x) - (B.x - A.x) * (C.y - A.y));

	float w2 = (point.y - A.y - w1 * (B.y - A.y)) / (C.y - A.y);

	if (w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1)
	{
		return true;//Point inside triangle
	}
	return false;
}

Rgb* SoftwareRenderer::FetchDataFromTexture(const char* path)
{
	//Read file and store data
	FILE* f = fopen(path, "rb");
	const uint32_t w = 5;
	const uint32_t h = 5;
	std::string strWidth = std::to_string(w);
	std::string strHeight = std::to_string(h);
	const int widthLength = strWidth.length();
	const int heightLength = strHeight.length();

	const int headerLength = 9 + widthLength + heightLength;
	unsigned char* header = new unsigned char[headerLength];
	fread(header, sizeof(unsigned char), headerLength, f);

	Rgb *data = new Rgb[w*h];

	fread(data, sizeof(Rgb), w*h, f);

	fclose(f);
	return &data[0];
}

void SoftwareRenderer::DrawTriangle(Vector2 v0, Vector2 v1, Vector2 v2)
{
	//Create vertices from params
	Vector2* pv0 = &v0;
	Vector2* pv1 = &v1;
	Vector2* pv2 = &v2;

	//Swap so v0 has lowest y and v2 has highest
	if (pv1->y < pv0->y)
	{
		std::swap(pv0, pv1);
	}
	if (pv2->y < pv1->y)
	{
		std::swap(pv1, pv2);
	}
	if (pv1->y < pv0->y)
	{
		std::swap(pv0, pv1);
	}

	//Flat top or flat bot triangle
	if (pv0->y == pv1->y) //Flat top
	{
		//Swap bottom vertices - pv0 has it lowest x valuei
	   //if (pv1->x < pv0->x) std::swap(pv0, pv1);
		if (pv0->x > pv1->x) std::swap(pv0, pv1);
		DrawFlatTopTriangle(*pv0, *pv1, *pv2);
	}
	else if (pv1->y == pv2->y) //Flat bot
	{
		//if (pv2->x < pv1->x)
		if (pv1->x > pv2->x) std::swap(pv1, pv2);
		DrawFlatBotTriangle(*pv0, *pv1, *pv2);
	}
	else //General triangle
	{
		const float alphaSplit =
			(pv1->y - pv0->y) /
			(pv2->y - pv0->y);
		const Vector2 vi = *pv0 + (*pv2 - *pv0) * alphaSplit;

		if (pv1->x < vi.x) //Major right triangle
		{
			DrawFlatBotTriangle(*pv0, *pv1, vi);
			DrawFlatTopTriangle(*pv1, vi, *pv2);
		}
		else //Major left triangle
		{
			DrawFlatBotTriangle(*pv0, vi, *pv1);
			DrawFlatTopTriangle(vi, *pv1, *pv2);
		}
	}
}

void SoftwareRenderer::DrawFlatTopTriangle(Vector2 v0, Vector2 v1, Vector2 v2)
{
	/*
	*	______
	*	|	 /
	*	|   /
	*	|  /
	*	| /
	*	|/
	*/
	Vertex vertex00(v0);
	Vertex vertex01(v1);
	Vertex vertex02(v2);
	Triangle tempTriangle(vertex00, vertex01, vertex02);

	//Slopes
	float m0 = (v2.x - v0.x) / (v2.y - v0.y);
	float m1 = (v2.x - v1.x) / (v2.y - v1.y);

	//Start & end scanlines in y
	const int yStart = (int)ceil(v0.y - 0.5f);
	const int yEnd = (int)ceil(v2.y - 0.5f); //Scanline after last line drawn (not included)

	//Iterate through scanline
	for (int y = yStart; y < yEnd; y++)
	{
		//Calculate start and end x of the scanline
		const float px0 = m0 * (float(y) + 0.5f - v0.y) + v0.x;
		const float px1 = m1 * (float(y) + 0.5f - v1.y) + v1.x;

		//Calculate start and end pixels of scanline
		const int xStart = (int)ceil(px0 - 0.5f);
		const int xEnd = (int)ceil(px1 - 0.5f);

		for (int x = xStart; x < xEnd; x++)
		{
			functionLamda(x, y, this->fetchTexture, this->rasterizeTexture, tempTriangle);
		}
	}
}

void SoftwareRenderer::DrawFlatBotTriangle(Vector2 v0, Vector2 v1, Vector2 v2)
{
	/*
	*
	*	|\
	*	| \
	*	|  \
	*	|   \
	*	|____\
	*/
	Vertex vertex00(v0);
	Vertex vertex01(v1);
	Vertex vertex02(v2);
	Triangle tempTriangle(vertex00, vertex01, vertex02);

	//Slopes
	float m0 = (v1.x - v0.x) / (v1.y - v0.y);
	float m1 = (v2.x - v0.x) / (v2.y - v0.y);

	//Start & end scanlines in y
	const int yStart = (int)ceil(v0.y - 0.5f);
	const int yEnd = (int)ceil(v2.y - 0.5f); //Scanline after last line drawn (not included)

	//Iterate through scanline
	for (int y = yStart; y < yEnd; y++)
	{
		//Calculate start and end x of the scanline
		const float px0 = m0 * (float(y) + 0.5f - v0.y) + v0.x;
		const float px1 = m1 * (float(y) + 0.5f - v0.y) + v0.x;

		//Calculate start and end pixels of scanline
		const int xStart = (int)ceil(px0 - 0.5f);
		const int xEnd = (int)ceil(px1 - 0.5f);

		//

		for (int x = xStart; x < xEnd; x++)
		{
			functionLamda(x, y, this->fetchTexture, this->rasterizeTexture, tempTriangle);
		}

		//Close file
	}
}