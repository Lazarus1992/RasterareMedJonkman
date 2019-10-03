#include "config.h"
#include "MeshResource.h"
#include <iostream>

using namespace std;

MeshResource::MeshResource()
{
}

MeshResource::~MeshResource()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void MeshResource::Setup(MeshName name)
{
	switch (name)
	{
	case Cube:
		currentMesh = Cube;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		//Position VBO && texcoord VBO
		glGenBuffers(1, &this->vboArray[VBO_Position]);
		glBindBuffer(GL_ARRAY_BUFFER, this->vboArray[VBO_Position]);
		glBufferData(GL_ARRAY_BUFFER, 48 * sizeof(vertexBuffer[0]), vertexBuffer, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, NULL);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid *)(sizeof(float) * 4));

		glGenBuffers(1, &this->ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), this->indexBuffer, GL_STATIC_DRAW);

		glBindVertexArray(0);
		break;
	case Obj:
		currentMesh = Obj;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(NUM_BUFFERS, vboArray);

		//VBO_Position
		glBindBuffer(GL_ARRAY_BUFFER, vboArray[VBO_Position]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//VBO_TexCoords
		// glBindBuffer(GL_ARRAY_BUFFER, vboArray[VBO_TexCoord]);
		// glBufferData(GL_ARRAY_BUFFER, sizeof(uvs[0]) * uvs.size(), &uvs[0], GL_STATIC_DRAW);
		// glEnableVertexAttribArray(1);
		// glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		// VBO_Normals
		glBindBuffer(GL_ARRAY_BUFFER, vboArray[VBO_Normal]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboArray[EBO_Faces]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices[0]) * vertexIndices.size(), &this->vertexIndices[0], GL_STATIC_DRAW);

		glBindVertexArray(0);
		break;
	case Quad:
		currentMesh = Quad;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		//Create vertex buffer
		glGenBuffers(1, &this->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(GLfloat), vertexBuffer, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 5, NULL);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float32) * 5, (GLvoid *)(sizeof(float32) * 3));

		//Create index buffer
		glGenBuffers(1, &this->ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), this->indexBuffer, GL_STATIC_DRAW);
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		break;

	case RayBeam:
		currentMesh = RayBeam;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		//Create vertex buffer
		glGenBuffers(1, &this->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), vertexBuffer, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glBindVertexArray(0);

		break;
	default:
		break;
	}
}

shared_ptr<MeshResource> MeshResource::CreateRay(Vector3 start, Vector3 end)
{
	shared_ptr<MeshResource> out = make_shared<MeshResource>();

	out->vertexBuffer = new GLfloat[6]
	{
		start.x, start.y, start.z,
		end.x, end.y, end.z
	};
	// out->vertexBuffer = new GLfloat[6]
	// {
	// 	1, 0, 0,
	// 	2, 0, 0
	// };

	out->Setup(RayBeam);
	return out;
}

void MeshResource::Draw()
{
	glBindVertexArray(vao);

	switch (currentMesh)
	{
	case Cube:
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		break;
	case Obj:
		glDrawElements(GL_TRIANGLES, vertexIndices.size(), GL_UNSIGNED_INT, 0);
		break;
	case Quad:
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		break;
	case Footman:
		glDrawElements(GL_TRIANGLES, vertexIndices.size(), GL_UNSIGNED_INT, 0);
		break;

	case RayBeam:
		glDrawArrays(GL_LINES, 0, 2);
		break;

	default:
		break;
	}

	glBindVertexArray(0);
}

bool MeshResource::LoadOBJ(const char *path)
{

	std::vector<Vector3> tempVertices;
	std::vector<Vector2> tempUvs;
	std::vector<Vector3> tempNormals;

	FILE *fp = fopen(path, "r");
	if (fp == nullptr)
	{
		printf("Impossible to open the file !\n");
		return false;
	}
	int count1 = 0;
	while (true)
	{
		char lineHeader[128];
		char line[256];

		//Set lineHeader to initial word of the line. Each loop fp is beeing moved to the next line in the file
		int res = fscanf(fp, "%s", lineHeader);

		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0)
		{
			Vector3 vertex;
			fscanf(fp, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tempVertices.push_back(vertex);
			int e = 3;
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			Vector2 uv;
			fscanf(fp, "%f %f\n", &uv.x, &uv.y);
			tempUvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			Vector3 normal;
			fscanf(fp, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tempNormals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{

			fseek(fp, 1, SEEK_CUR);
			fgets(line, sizeof(line), fp);

			std::vector<std::string> tokens = SplitString(line, ' ');
			//Special case for some line endings
			if (tokens[tokens.size() - 1] == "\r\n")
			{
				tokens.resize(3);
			}

			int tokensize = tokens.size();
			if (tokensize == 3)
			{
				for (int i = 0; i < tokens.size(); i++) // x/x/x
				{
					std::vector<std::string> faceTokens = SplitString(tokens[i].c_str(), '/');

					int vertex = atoi(faceTokens[0].c_str()) - 1;
					int uvCoord = atoi(faceTokens[1].c_str()) - 1;
					int normal = atoi(faceTokens[2].c_str()) - 1;

					vertexIndices.push_back(vertex);
					uvIndices.push_back(uvCoord);
					normalIndices.push_back(normal);
				}
			}

			if (tokensize == 4)
			{
				for (int loopCount = 0; loopCount < 2; loopCount++)
				{
					for (int i = 0; i < tokens.size(); i++) // x/x/x
					{
						if (loopCount == 1 && i == 1)
						{
							continue;
						}

						std::vector<std::string> faceTokens = SplitString(tokens[i].c_str(), '/');

						int vertex = atoi(faceTokens[0].c_str()) - 1;
						int uvCoord = atoi(faceTokens[1].c_str()) - 1;
						int normal = atoi(faceTokens[2].c_str()) - 1;

						vertexIndices.push_back(vertex);
						uvIndices.push_back(uvCoord);
						normalIndices.push_back(normal);
					}
				}
			}
		}
	}
	vertices = tempVertices;
	uvs = tempUvs;
	normals = tempNormals;
	//scale
	// for (int i = 0; i < vertices.size(); i++)
	// {
	// 	// vertices[i].v[0] = vertices[i].v[0] / 8;
	// 	// vertices[i].v[1] = vertices[i].v[1] / 8;
	// 	// vertices[i].v[2] = vertices[i].v[2] / 8;
	// }
	objLoaded = true;

	return true;
}

std::vector<std::string> MeshResource::SplitString(const std::string &str, char delim)
{
	std::vector<std::string> elems;

	const char *cstr = str.c_str();
	unsigned int strLength = str.length();
	unsigned int start = 0;
	unsigned int end = 0;

	while (end <= strLength)
	{
		while (end <= strLength)
		{
			if (cstr[end] == delim)
				break;
			end++;
		}

		const char *subString = str.substr(start, end - start).c_str();
		elems.push_back(subString);
		start = end + 1;
		end = start;
	}

	return elems;
}

shared_ptr<MeshResource> MeshResource::CreateObj(int objIndex)
{

	shared_ptr<MeshResource> out = make_shared<MeshResource>();

	// out->LoadOBJ("projects//MathLib4D//Obj//teapot//teapot.obj");
	// out->LoadOBJ("projects//MathLib4D//Obj//cat//cat.obj");
	// out->LoadOBJ("projects//MathLib4D//Obj//planet//earth.obj");
	
	switch (objIndex)
	{
		case 0:
			// out->LoadOBJ("projects//MathLib4D//Obj//SimpleSphere//sphere.obj");
			out->LoadOBJ("projects//MathLib4D//Obj//teapot//teapot.obj");
			out->Setup(Obj);
			break;
		default:
			break;
	}

	return out;
}

shared_ptr<MeshResource> MeshResource::CreateCube_t()
{
	shared_ptr<MeshResource> out = make_shared<MeshResource>();
	out->vertexBuffer = new GLfloat[48]{
		-.5f, -.5f, .5f, 1, //0
		0, 0,

		-.5f, .5f, .5f, 1, //1
		1, 0,

		.5f, .5f, .5f, 1, //2
		1, 1,

		.5f, -.5f, .5f, 1, //3
		0, 1,

		-.5f, -.5f, -.5f, 1, //4
		0, 0,

		-.5f, .5f, -.5f, 1, //5
		1, 0,

		.5f, .5f, -.5f, 1, //6
		1, 1,

		.5f, -.5f, -.5f, 1, //7
		0, 1};

	out->indexBuffer = new GLuint[36]{
		0, 2, 1, 0, 3, 2,
		4, 3, 0, 4, 7, 3,
		4, 1, 5, 4, 0, 1,
		3, 6, 2, 3, 7, 6,
		1, 6, 5, 1, 2, 6,
		7, 5, 6, 7, 4, 5};

	out->Setup(Cube);
	return out;
}

shared_ptr<MeshResource> MeshResource::CreateQuad_t()
{
	shared_ptr<MeshResource> out = make_shared<MeshResource>();

	//float scale = 4.0f;
	//out->vertexBuffer = new GLfloat[20]
	//{

	//	-.5f * 2 * scale, .5f * scale, .5f * scale, //0 //Topleft
	//	0, 0,

	//	.5f * 2 * scale, .5f * scale, .5f * scale, //1 //Topright
	//	1, 0,

	//	.5f * 2 * scale, -.5f * scale, .5f * scale, //2 //Bottomleft
	//	1, 1,

	//	-.5f * 2 * scale, -.5f * scale, .5f * scale, //3 //Bottomright
	//	0, 1

	//};

	float scale = 1.0f;
	out->vertexBuffer = new GLfloat[20]
	{

		-.5f * scale, .5f * scale, .5f * scale, //0 //Topleft
		0, 0,

		.5f * scale, .5f * scale, .5f * scale, //1 //Topright
		1, 0,

		.5f * scale, -.5f * scale, .5f * scale, //2 //Bottomleft
		1, 1,

		-.5f * scale, -.5f * scale, .5f * scale, //3 //Bottomright
		0, 1

	};


	out->indexBuffer = new GLuint[6]{
		0, 1, 2,
		2, 3, 0

	};

	out->Setup(Quad);
	return out;
}



MeshResource *MeshResource::CreateCube_c()
{
	MeshResource *out = new MeshResource();
	out->vertexBuffer = new GLfloat[64] //4 first are cube position, the rest are texcoords
		{

			-.5f, -.5f, .5f, 1, //0
			0, 0, 1, 1,

			-.5f, .5f, .5f, 1, //1
			1, 0, 0, 1,

			.5f, .5f, .5f, 1, //2
			0, 1, 0, 1,

			.5f, -.5f, .5f, 1, //3
			1, 1, 0, 1,

			-.5f, -.5f, -.5f, 1, //4
			1, 1, 1, 1,

			-.5f, .5f, -.5f, 1, //5
			1, 0, 0, 1,

			.5f, .5f, -.5f, 1, //6
			1, 0, 1, 1,

			.5f, -.5f, -.5f, 1, //7
			0, 0, 1, 1};

	out->indexBuffer = new GLuint[36]{
		0, 2, 1, 0, 3, 2,
		4, 3, 0, 4, 7, 3,
		4, 1, 5, 4, 0, 1,
		3, 6, 2, 3, 7, 6,
		1, 6, 5, 1, 2, 6,
		7, 5, 6, 7, 4, 5};

	out->Setup(Cube);
	return out;
}

MeshResource *MeshResource::CreateQuad_c()
{
	MeshResource *out = new MeshResource();
	out->vertexBuffer = new GLfloat[28]{
		-0.5f, 0.5f, -1,  // pos 0
		0, 1.0f, 0, 1,	// color 0
		0.5f, 0.5f, -1,   // pos 1
		0, 0, 1.0f, 1,	// color 1
		0.5f, -0.5f, -1,  // pos 2
		0, 1.0f, 0, 1,	// color 2
		-0.5f, -0.5f, -1, // pos 3
		0, 0, 1.0f, 1	 // color 3
	};

	out->indexBuffer = new GLuint[6]{
		0, 1, 2,
		2, 3, 0};

	out->Setup(Cube);
	return out;
}

void MeshResource::Draw_cube_t()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 6, NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float32) * 6, (GLvoid *)(sizeof(float32) * 4));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
