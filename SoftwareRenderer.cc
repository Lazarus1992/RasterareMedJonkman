#include "SoftwareRenderer.h"



SoftwareRenderer::SoftwareRenderer()
{
	functionLamda = [this](int xCoord, int yCoord, Rgb* fetchTexture, Rgb* rasterizedTexture)
	{
		Vector2 v0 = { 5.0f, 5.0f }; //u: 1, v: 1	Nere höger
		Vector2 v1 = { 0.0f, 0.0f }; //u: 0, v: 0	Uppe vänster
		Vector2 v2 = { 0.0f, 5.0f }; //u: 0, v: 1 	Nere vänster	

		Vector2 uv0 = { 1, 1 };
		Vector2 uv1 = { 0, 0 };
		Vector2 uv2 = { 0, 1 };



		cout << "Inside lambda" << endl;

		float area = EdgeFunction(v0, v1, v2);
		Vector2 p = { (float)xCoord, (float)yCoord };
		float w0 = EdgeFunction(v1, v2, p);
		float w1 = EdgeFunction(v2, v0, p);
		float w2 = EdgeFunction(v0, v1, p);

		if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
			w0 /= area;
			w1 /= area;
			w2 /= area;

			Vector2 textureUV = uv0 * w0 + uv1 * w1 + uv2 * w2;
			float row = this->imageHeight;
			float column = this->imageWidth;
			int pixelToGet = textureUV.y * row * (float)this->imageWidth + textureUV.x * column;

			////Row * width + col
			//this->rasterizeTexture[yCoord * this->imageWidth + xCoord][0] = 1;
			//this->rasterizeTexture[yCoord * this->imageWidth + xCoord][1] = 1;
			//this->rasterizeTexture[yCoord * this->imageWidth + xCoord][2] = 1;

			this->rasterizeTexture[yCoord * this->imageWidth + xCoord][0] = this->fetchTexture[pixelToGet][0];
			this->rasterizeTexture[yCoord * this->imageWidth + xCoord][1] = this->fetchTexture[pixelToGet][1];
			this->rasterizeTexture[yCoord * this->imageWidth + xCoord][2] = this->fetchTexture[pixelToGet][2];
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

void SoftwareRenderer::Init()
{
	//FILE *fp = fopen("TextureToWriteTo.ppm", "wb");
	filePtr = fopen("TextureToWriteTo.ppm", "wb");
	//(void)fprintf(fp, "P6\n%d %d\n255\n", this->imageHeight, this->imageWidth);
	//(void)fwrite(this->rasterizeTexture, 1, this->imageWidth * this->imageHeight * 3, fp);
	//return fp;
	(void)fprintf(filePtr, "P6\n%d %d\n255\n", this->imageHeight, this->imageWidth);
	//return filePtr;
}

void SoftwareRenderer::Shutdown()
{
	(void)fwrite(this->rasterizeTexture, 1, this->imageWidth * this->imageHeight * 3, filePtr);
	(void)fclose(this->filePtr);
	//(void)fclose(fp);
}

inline
float SoftwareRenderer::EdgeFunction(Vector2 a, Vector2 b, Vector2 c)
{
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
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
	if (pv1->y < pv0->y) std::swap(pv0, pv1);
	if (pv2->y < pv1->y) std::swap(pv1, pv2);
	if (pv1->y < pv0->y) std::swap(pv0, pv1);

	//Flat top or flat bot triangle
	if (pv0->y == pv1->y) //Flat top
	{
		//Swap bottom vertices - pv0 has it lowest x value
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
			functionLamda(x, y, this->fetchTexture, this->rasterizeTexture);
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

		//Open file

		for (int x = xStart; x < xEnd; x++)
		{
			functionLamda(x, y, this->fetchTexture, this->rasterizeTexture);
		}

		//Close file
	}
}