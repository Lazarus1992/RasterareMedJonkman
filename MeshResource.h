#pragma once
#include "core/app.h"
#include <memory>
#include "ShaderObject.h"
#include <vector>
#include "MathLib4D.h"

enum MeshName
{
	Cube,
	Obj,
	Quad,
	Footman,
	RayBeam
};

enum VBO_Index
{
	VBO_Position,
	VBO_TexCoord,
	VBO_Normal,
	VBO_Weight,
	VBO_JointIndices,
	VBO_Tangents,
	VBO_Binormals,
	EBO_Faces
};

class MeshResource
{
  private:
	static const unsigned int NUM_BUFFERS = 8;

  public:

	GLfloat *vertexBuffer;
	GLuint *indexBuffer;
	GLuint vbo;
	GLuint ebo;
	GLuint vao;
	GLuint vboArray[NUM_BUFFERS];
	MeshName currentMesh;

	bool objLoaded = false;

	vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	vector<Vector3> vertices;
	vector<Vector2> uvs;
	vector<Vector3> normals;
	

	MeshResource();
	void Setup(MeshName name);
	void Draw_cube_t();
	void Draw_cube_c();
	void Draw_quad_t();

	static MeshResource *CreateQuad_c();
	static MeshResource *CreateCube_c();
	static shared_ptr<MeshResource> CreateRay(Vector3 start, Vector3 end);
	std::vector<std::string> SplitString(const std::string &s, char delim);
	void Draw();
	bool LoadOBJ(const char *path);
	static shared_ptr<MeshResource> CreateObj(int objIndex);
	static shared_ptr<MeshResource> CreateCube_t();
	static shared_ptr<MeshResource> CreateQuad_t();
	~MeshResource();
};
