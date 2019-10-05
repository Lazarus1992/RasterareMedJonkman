#include "SoftwareRenderer.h"



SoftwareRenderer::SoftwareRenderer()
{
	//this->texture.Bind("", 0)
}


SoftwareRenderer::~SoftwareRenderer()
{
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
	}
}

void SoftwareRenderer::DrawFlatBotTriangle(Vector2 v0, Vector2 v1, Vector2 v2)
{

}