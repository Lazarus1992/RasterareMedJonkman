#include "SoftwareRenderer.h"
#include "Math.h"



SoftwareRenderer::SoftwareRenderer()
{
	functionLamda = [this](int xCoord, int yCoord, Rgb* fetchTexture, Rgb* rasterizedTexture, Triangle triangle)
	{
		bool useFetchTexture = true;
		//bool useFetchTexture = false;
		//bool useEdgeFunction = true;
		bool useEdgeFunction = false;
		//float pointOffset = useFetchTexture ? 0 : 0.5f;
		float pointOffset = useFetchTexture ? 2 : 0.5f;

		Vector2 vec0 = triangle.v0.position;
		Vector2 vec1 = triangle.v1.position;
		Vector2 vec2 = triangle.v2.position;

		//Create UVs from vertex positions
		Vector2 uv0 = { vec0.x / this->imageWidth, vec0.y / this->imageHeight };
		Vector2 uv1 = { vec1.x / this->imageWidth, vec1.y / this->imageHeight };
		Vector2 uv2 = { vec2.x / this->imageWidth, vec2.y / this->imageHeight };

		//Vector2 p = { (float)xCoord + pointOffset, (float)yCoord + pointOffset };
		
		Weights w;
		Barycentric((float)xCoord, (float)yCoord, triangle.v0, triangle.v1, triangle.v2, w);
		float area = EdgeFunction(vec0, vec1, vec2);
		//float w0 = EdgeFunction(vec1, vec2, p);
		//float w1 = EdgeFunction(vec2, vec0, p);
		//float w2 = EdgeFunction(vec0, vec1, p);
		float w0 = w.w1;
		float w1 = w.w2;
		float w2 = w.w3;

		Vector2 textureUV = uv0 * w0 + uv1 * w1 + uv2 * w2;
		float row = this->imageHeight;
		float column = this->imageWidth;
		int pixelToGet = round(textureUV.y * row * column + textureUV.x * column);

		if (!useEdgeFunction)
		{
			this->rasterizeTexture[yCoord * this->imageWidth + xCoord][0] = this->fetchTexture[pixelToGet][0];
			this->rasterizeTexture[yCoord * this->imageWidth + xCoord][1] = this->fetchTexture[pixelToGet][1];
			this->rasterizeTexture[yCoord * this->imageWidth + xCoord][2] = this->fetchTexture[pixelToGet][2];
		}

		//Check if point is in triangle and color it
		//if (useEdgeFunction && this->PointInTriangle(vec0, vec1, vec2, p + Vector2(0.5f, 0.5f))) {
		//	w0 /= area;
		//	w1 /= area;
		//	w2 /= area;

		//	Vector4 fPointLightColor(0.8f, .1f, .1f, 1.0f);
		//	Vector3 fNormal(0, 0, 1);
		//	Vector3 fLight(70.0f, 20.0f, 5.0f);
		//	//Vector3 fLight(50.0f, 60.0f, 5.0f);
		//	Vector3 fVertexRelativePosition(xCoord - fLight.x + pointOffset, yCoord - fLight.y + pointOffset, 0.0f - fLight.z);
		//	Vector3 N = fNormal.Normalize();
		//	Vector3 L = (fLight - fVertexRelativePosition).Normalize();
		//	Vector3 E = (fVertexRelativePosition * -1.0f).Normalize();
		//	Vector3 H = (L + E).Normalize();

		//	float fPointLightIntensity = 10.0f;

		//	//Specular + diffuse code
		//	float diffuse_intensity = max(N.Dot(L), 0.0f);
		//	Vector4 diffuse_final = fPointLightColor * diffuse_intensity;

		//	float spec_intensity = pow(max(N.Dot(H), 0.0f), 30);
		//	Vector4 spec_final = Vector4(0.1, 0.1, 0.1, 1.0) * spec_intensity * fPointLightIntensity;

		//	//Vector4 outColor = diffuse_final + spec_final;
		//	Vector4 outColor = diffuse_final;

		//	Vector2 textureUV = uv0 * w0 + uv1 * w1 + uv2 * w2;
		//	float row = this->imageHeight;
		//	float column = this->imageWidth;
		//	int pixelToGet = round(textureUV.y * row * column + textureUV.x * column);

		//	//Row * width + col
		//	if (useFetchTexture)
		//	{
		//		this->rasterizeTexture[yCoord * this->imageWidth + xCoord][0] = this->fetchTexture[pixelToGet][0];
		//		this->rasterizeTexture[yCoord * this->imageWidth + xCoord][1] = this->fetchTexture[pixelToGet][1];
		//		this->rasterizeTexture[yCoord * this->imageWidth + xCoord][2] = this->fetchTexture[pixelToGet][2];
		//	}
		//	else
		//	{
		//		this->rasterizeTexture[yCoord * this->imageWidth + xCoord][0] = max(outColor[0] * 255.0f, 0.0f);
		//		this->rasterizeTexture[yCoord * this->imageWidth + xCoord][1] = max(outColor[1] * 255.0f, 0.0f);
		//		this->rasterizeTexture[yCoord * this->imageWidth + xCoord][2] = max(outColor[2] * 255.0f, 0.0f);
		//	}


		//}
		//else {
		//	cout << "not in triangle" << endl;
		//}

	};

	int x = 1;
	int y = 1;

	this->fetchTexture = FetchDataFromTexture("TextureToFetchFrom.ppm");
	this->rasterizeTexture = new Rgb[this->imageWidth * this->imageHeight];
}

SoftwareRenderer::~SoftwareRenderer()
{
}

void SoftwareRenderer::Barycentric(const float x, const float y, const Vertex& v1, const Vertex& v2, const Vertex& v3, Weights& w)
{
	w.w1 = (((v2.position.y - v3.position.y)*(x - v3.position.x)) + ((v3.position.x - v2.position.x)*(y - v3.position.y))) /
		(((v2.position.y - v3.position.y)*(v1.position.x - v3.position.x)) + ((v3.position.x - v2.position.x)*(v1.position.y - v3.position.y)));
	w.w1 = std::max(0.0f, std::min(1.0f, w.w1));

	w.w2 = (((v3.position.y - v1.position.y)*(x - v3.position.x)) + ((v1.position.x - v3.position.x)*(y - v3.position.y))) /
		(((v2.position.y - v3.position.y)*(v1.position.x - v3.position.x)) + ((v3.position.x - v2.position.x)*(v1.position.y - v3.position.y)));
	w.w2 = std::max(0.0f, std::min(1.0f, w.w2));

	w.w3 = 1 - w.w1 - w.w2;
	w.w3 = std::max(0.0f, std::min(1.0f, w.w3));
}

void SoftwareRenderer::Bresenhams(Vector2 p0, Vector2 p1, vector<Vector2>& pointsOnLine)
{
	float x0, y0, x1, y1;
	x0 = p0.x;
	y0 = p0.y;
	x1 = p1.x;
	y1 = p1.y;
	if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1) {
			PlotLineLow(x1, y1, x0, y0, pointsOnLine);
		}
		else
		{
			PlotLineLow(x0, y0, x1, y1, pointsOnLine);
		}
	}
	else
	{
		if (y0 > y1)
		{
			PlotLineHigh(x1, y1, x0, y0, pointsOnLine);
		}
		else
		{
			PlotLineHigh(x0, y0, x1, y1, pointsOnLine);
		}
	}
}

void SoftwareRenderer::PlotLineHigh(float x0, float y0, float x1, float y1, vector<Vector2>& pointsOnLine)
{
	float dx = x1 - x0;
	float dy = y1 - y0;
	int xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}

	float D = 2 * dx - dy;
	float x = x0;


	for (int y = y0; y < y1; y++)
	{
		pointsOnLine.push_back(Vector2(x, y));
		if (D > 0)
		{
			x = x + xi;
			D = D - 2 * dy;
		}
		D = D + 2 * dx;
	}
}

void SoftwareRenderer::PlotLineLow(float x0, float y0, float x1, float y1, vector<Vector2>& pointsOnLine)
{
	float dx = x1 - x0;
	float dy = y1 - y0;
	int yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	float D = 2 * dy - dx;
	float y = y0;

	for (int x = x0; x < x1; x++)
	{
		pointsOnLine.push_back(Vector2(x, y));
		if (D > 0)
		{
			y = y + yi;
			D = D - 2 * dx;
		}
		D = D + 2 * dy;
	}
}

void SoftwareRenderer::Init()
{
	//Create quad
	const int indexBufferSize = 6;
	const int vertexBufferSize = 8;
	const int stride = 2;
	vector<Vertex> vertices;
	for (int i = 0; i < indexBufferSize; i++)
	{
		int index = *(this->indexBuffer + i);
		int vertexBufferValue = *(this->vertexBuffer + index * stride);
		int vertexBufferValuePlusOne = *(this->vertexBuffer + (index * stride) + 1);

		Vertex tempVertex0(Vector2(vertexBufferValue, vertexBufferValuePlusOne));
		vertices.push_back(tempVertex0);
	}

	for (int i = 0; i < vertices.size(); i += 3)
	{
		Triangle tempTriangle(vertices[i], vertices[i + 1], vertices[i + 2]);
		triangles.push_back(tempTriangle);
	}

	this->filePtr = fopen("TextureToWriteTo.ppm", "wb");
	(void)fprintf(this->filePtr, "P6\n%d %d\n255\n", this->imageHeight, this->imageWidth);

}

void SoftwareRenderer::Start()
{
	//Iterate through all indices and create triangles
	for (int i = 0; i < triangles.size(); i++)
	{
		//Translate triangles
		Vector4 v0_translated = this->mvpMatrix * Vector4(triangles[i].v0.position.x, triangles[i].v0.position.y, 0, 1);
		Vector4 v1_translated = this->mvpMatrix * Vector4(triangles[i].v1.position.x, triangles[i].v1.position.y, 0, 1);
		Vector4 v2_translated = this->mvpMatrix * Vector4(triangles[i].v2.position.x, triangles[i].v2.position.y, 0, 1);

		DrawTriangle(Vector2(v0_translated[0], v0_translated[1]), Vector2(v1_translated[0], v1_translated[1]), Vector2(v2_translated[0], v2_translated[1]));
	}
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
	const uint32_t w = 200;
	const uint32_t h = 200;
	std::string strWidth = std::to_string(w);
	std::string strHeight = std::to_string(h);
	const int widthLength = strWidth.length();
	const int heightLength = strHeight.length();

	const int headerLength = 9;
	const int dataLength = headerLength + widthLength + heightLength;
	unsigned char* file = new unsigned char[dataLength];
	fread(file, sizeof(unsigned char), dataLength, f);

	Rgb *data = new Rgb[w*h];

	fread(data, sizeof(Rgb), w*h, f);

	fclose(f);
	return &data[0];
}

/*
*	This function checks if the triangle we're drawing is a flat top, flat bot or a general triangle that should be split.
*/
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
		if (pv0->x > pv1->x) std::swap(pv0, pv1);
		DrawFlatTopTriangle(*pv0, *pv1, *pv2);
	}
	else if (pv1->y == pv2->y) //Flat bot
	{
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

/*
*	This function finds a start and an end to each line which then gets scanned and coloured.
*/
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

	//Slopes - get slopes from v2 to other points
	//float m0 = (v2.x - v0.x) / (v2.y - v0.y);
	//float m1 = (v2.x - v1.x) / (v2.y - v1.y);

	////Start & end scanlines in y
	//const int yStart = (int)ceil(v0.y - 0.5f);
	//const int yEnd = (int)ceil(v2.y - 0.5f); //Scanline after last line drawn (not included)

	//Bresenham's
	//if (m0 != 0)
	//{
	//	int e = 3;
	//}

	//if (m1 != 0)
	//{
	//	int e = 3;
	//}

	vector<Vector2> leftLine;
	vector<Vector2> rightLine;

	Bresenhams(v0, v2, leftLine);
	Bresenhams(v1, v2, rightLine);

	int lineLength = leftLine.size();
	float yStart = leftLine[0].y;
	float yEnd = leftLine[lineLength-1].y;

	//for (int y = 0; y < lineLength; y++)
	for (int y = yStart; y < yEnd + 1; y++)
	{
		float xStart = leftLine[y].x;
		float xEnd = rightLine[y].x;
		for (int x = xStart; x < xEnd; x++)
		{
			functionLamda(x, y, this->fetchTexture, this->rasterizeTexture, tempTriangle);
		}
		//float x = pointsOnLine2[i].x;
		//float y = pointsOnLine2[i].y;
		//functionLamda(x, y, this->fetchTexture, this->rasterizeTexture, tempTriangle);
	}



	////Iterate through scanline
	//for (int y = yStart; y < yEnd; y++)
	//{
	//	//Store end of lines for every y as xStart and xEnd
	//	//Line line;
	//	//Bresenhams(line)

	//	////Edge function
	//	////Calculate start and end x of the scanline
	//	//const float px0 = m0 * (float(y) + 0.5f - v0.y) + v0.x;
	//	//const float px1 = m1 * (float(y) + 0.5f - v1.y) + v1.x;

	//	////Calculate start and end pixels of scanline
	//	//const int xStart = (int)ceil(px0 - 0.5f);
	//	//const int xEnd = (int)ceil(px1 - 0.5f);

	//	//for (int x = xStart; x < xEnd; x++)
	//	//{
	//	//	functionLamda(x, y, this->fetchTexture, this->rasterizeTexture, tempTriangle);
	//	//}
	//}
}

/*
*	This function finds a start and an end to each line which then gets scanned and coloured.
*/
void SoftwareRenderer::DrawFlatBotTriangle(Vector2 v0, Vector2 v1, Vector2 v2)
{
	/*
	*
	*	    /|
	*	   / |
	*	  /  |
	*	 /   |
	*	/____|
	*/
	Vertex vertex00(v0);
	Vertex vertex01(v1);
	Vertex vertex02(v2);
	Triangle tempTriangle(vertex00, vertex01, vertex02);

	vector<Vector2> leftLine;
	vector<Vector2> rightLine;

	Vector2 test0(3,2);
	Vector2 test1(15,5);
	vector<Vector2> testLine;
	Bresenhams(test0, test1, testLine);

	Bresenhams(v1, v0, leftLine);
	Bresenhams(v2, v0, rightLine);

	int lineLength = leftLine.size();
	float yStart = leftLine[0].y;
	float yEnd = leftLine[lineLength - 1].y;

	//for (int y = 0; y < lineLength; y++)
	for (int y = yStart; y < yEnd + 1; y++)
	{
		float xStart = leftLine[y].x;
		float xEnd = rightLine[y].x;
		for (int x = xStart; x < xEnd; x++)
		{
			functionLamda(x, y, this->fetchTexture, this->rasterizeTexture, tempTriangle);
		}
		//float x = pointsOnLine2[i].x;
		//float y = pointsOnLine2[i].y;
		//functionLamda(x, y, this->fetchTexture, this->rasterizeTexture, tempTriangle);
	}

	////Slopes
	//float m0 = (v1.x - v0.x) / (v1.y - v0.y);
	//float m1 = (v2.x - v0.x) / (v2.y - v0.y);

	////Start & end scanlines in y
	//const int yStart = (int)ceil(v0.y - 0.5f);
	//const int yEnd = (int)ceil(v2.y - 0.5f); //Scanline after last line drawn (not included)

	////Iterate through scanline
	//for (int y = yStart; y < yEnd; y++)
	//{
	//	//Calculate start and end x of the scanline
	//	const float px0 = m0 * (float(y) + 0.5f - v0.y) + v0.x;
	//	const float px1 = m1 * (float(y) + 0.5f - v0.y) + v0.x;

	//	//Calculate start and end pixels of scanline
	//	const int xStart = (int)ceil(px0 - 0.5f);
	//	const int xEnd = (int)ceil(px1 - 0.5f);

	//	for (int x = xStart; x < xEnd; x++)
	//	{
	//		functionLamda(x, y, this->fetchTexture, this->rasterizeTexture, tempTriangle);
	//	}
	//}
}