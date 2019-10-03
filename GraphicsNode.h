#pragma once
#include "core/app.h"
#include "MeshResource.h"
#include "TextureResource.h"
#include "ShaderObject.h"
#include "MathLib4D.h"
#include <iostream>
#include <memory>
#include <string.h>

using namespace std;

//class PointLight
//{
//
//};

class GraphicsNode
{
  private:
	shared_ptr<ShaderObject> shader_;
	shared_ptr<MeshResource> mesh_;
	shared_ptr<TextureResource> tex_;
	MatrixLib4D transform; //Send to shader

  public:
	std::string name;
	int index;
	int parentIndex;

	//Temp float position variables for debug
	float positionX;
	float positionY;
	float positionZ;

	float translateX = 0;
	float translateY = 0;
	float translateZ = 0;

	MatrixLib4D localTransform;
	MatrixLib4D worldTransform;
	MatrixLib4D matView;
	MatrixLib4D matRot;

	GraphicsNode *parent;
	std::vector<GraphicsNode *> children;

	GraphicsNode();
	~GraphicsNode();

	void Setup(int shaderID);

	void SetShader(shared_ptr<ShaderObject> shader);
	shared_ptr<ShaderObject> GetShader();

	void SetMesh(shared_ptr<MeshResource> mesh_);
	shared_ptr<MeshResource> GetMesh();

	void SetTexture(shared_ptr<TextureResource> tex_);
	shared_ptr<TextureResource> GetTexture();

	void Draw();

	bool doOnce = true;
};
