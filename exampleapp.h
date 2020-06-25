#pragma once

#include "core/app.h"
#include "render/window.h"
#include "MeshResource.h"
#include "PointLight.h"
#include "GraphicsNode.h"
#include <memory>
#include <map>
#include "im3d.h"
#include "Ray.h"
#include "SoftwareRenderer.h"

//typedef float Vec2[2];
//typedef float Vec3[3];


class JontesProjekt : public Core::App
{
  public:
	JontesProjekt();
	~JontesProjekt();
	void DrawUI();
	void KeyPress();
	bool Open();
	void Run();

  private:

	//View
	Vector3 position;
	Vector3 direction = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 right = Vector3(1.0f, 0.0f, 0.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	MatrixLib4D testMatrixProj;
	MatrixLib4D testMatrixView;
	MatrixLib4D inverseProjectionMatrix;
	MatrixLib4D inverseViewMatrix;

	float deltaTime; //Time since last frame
	int currentClip = 7;
	map<int, int> clipIndex_numKeys;
	GraphicsNode skin;
	std::vector<GraphicsNode *> graphicsNodes;
	std::vector<GraphicsNode *> rays;

	float translateX = 0;
	float translateY = 0;
	float translateZ = 0;
	int nodeToRotate = 0;

	bool breaks = false;

	float mouseX = 400;
	float mouseY = 300;
	float newX = 400;
	float newY = 300;

	float cameraSpeed = 0.3f;
	float dX;
	float dY;
	float multiplierX; //14.48 / windowX
	float multiplierY; //11.13 / windowY
	float mouseLeft = false;
	float mouseRight = false;
	bool doOnce = true;

	float windowX = 1024;
	float windowY = 768;
	float horizontalAngle = 3.14159f;
	float verticalAngle = 0.0f;
	float mouseSpeed = 0.005f;
	Vector3 rayWorld;
	Ray ray;

	MatrixLib4D modelMatrix;
	MatrixLib4D viewMatrix;
	MatrixLib4D projectionMatrix;
	PointLight pointLight;

	const float cameraInitY = 0;
	const float cameraInitZ = 0;

	bool keyW = false;
	bool keyA = false;
	bool keyS = false;
	bool keyD = false;
	bool keyQ = false;
	bool keyE = false;
	bool keyF = false;
	bool keyR = false;
	bool keyC = false;

	int debugCount = 0;

	std::chrono::high_resolution_clock::time_point start, end;
	std::chrono::duration<float> duration;
	Display::Window *window;
};

