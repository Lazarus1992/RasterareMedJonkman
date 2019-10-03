#include "GraphicsNode.h"

GraphicsNode::GraphicsNode()
{
}
GraphicsNode::~GraphicsNode()
{
}

void GraphicsNode::SetShader(shared_ptr<ShaderObject> shader_)
{
	this->shader_ = shader_;
}

shared_ptr<ShaderObject> GraphicsNode::GetShader()
{
	return this->shader_;
}

void GraphicsNode::SetMesh(shared_ptr<MeshResource> mesh_)
{
	this->mesh_ = mesh_;
}

shared_ptr<MeshResource> GraphicsNode::GetMesh()
{
	return this->mesh_;
}

void GraphicsNode::SetTexture(shared_ptr<TextureResource> tex_)
{
	this->tex_ = tex_;
}

shared_ptr<TextureResource> GraphicsNode::GetTexture()
{
	return this->tex_;
}

void GraphicsNode::Draw()
{

	if (doOnce)
	{
		doOnce = false;
		 //tex_->Bind("projects/MathLib4D/Skeleton/footman/Footman_Diffuse.tga", 0);
		 tex_->Bind("first1.ppm", 0);
		//tex_->Bind("raster2dasd.ppm", 0);
		// tex_->Bind("projects/MathLib4D/Skeleton/footman/Footman_Specular.tga", 1);
		// tex_->Bind("projects/MathLib4D/Skeleton/footman/Footman_Normal.tga", 2);
	}

	mesh_->Draw();
}

void GraphicsNode::Setup(int shaderID)
{
	mesh_ = std::make_shared<MeshResource>();
	tex_ = std::make_shared<TextureResource>();
	shader_ = std::make_shared<ShaderObject>();
	shader_->SetupShaders(shaderID);
	shader_->Apply();
}
