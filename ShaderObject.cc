#include "ShaderObject.h"

ShaderObject::ShaderObject()
{
	// ifstream file1, file2;

	// string fileName1 = "projects//MathLib4D//Shaders//vsPhysics.glsl";
	// file1.open((fileName1).c_str());
	// string line1;

	// if (file1.is_open())
	// {
	// 	while (file1.good())
	// 	{
	// 		getline(file1, line1);
	// 		output1.append(line1 + "\n");
	// 	}
	// }
	// else
	// {
	// 	cerr << "Unable to load VertexshaderObject: " << fileName1 << endl;
	// }

	// string fileName2 = "projects//MathLib4D//Shaders//fsPhysics.glsl";
	// file2.open((fileName2).c_str());
	// string line2;

	// if (file2.is_open())
	// {
	// 	while (file2.good())
	// 	{
	// 		getline(file2, line2);
	// 		output2.append(line2 + "\n");
	// 	}
	// }
	// else
	// {
	// 	cerr << "Unable to load FragmentshaderObject: " << fileName2 << endl;
	// }



}

void ShaderObject::SetupShaders(int shaderID)
{
	string filenameVS;
	string filenameFS;

	switch (shaderID)
	{
		case 0:
			filenameVS = "projects//MathLib4D//Shaders//vs.glsl";
			filenameFS = "projects//MathLib4D//Shaders//fs.glsl";
			break;

		case 1:
			filenameVS = "projects//MathLib4D//Shaders//vsPhysics.glsl";
			filenameFS = "projects//MathLib4D//Shaders//fsPhysics.glsl";
			break;
	
		default:
			break;
	}
	LoadShader(filenameVS, filenameFS);

	const GLchar* vstest = output1.c_str();
	const GLchar* pstest = output2.c_str();
	// setup vertex shader
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLint length = std::strlen(vstest);
	glShaderSource(this->vertexShader, 1, &vstest, &length);
	glCompileShader(this->vertexShader);

	// get error log
	GLint shaderLogSize;
	glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetShaderInfoLog(this->vertexShader, shaderLogSize, NULL, buf);
		printf("[SHADER COMPILE ERROR]: %s", buf);
		delete[] buf;
	}

	// setup pixel shader
	this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
	length = std::strlen(pstest);
	glShaderSource(this->pixelShader, 1, &pstest, &length);
	glCompileShader(this->pixelShader);

	// get error log
	glGetShaderiv(this->pixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetShaderInfoLog(this->pixelShader, shaderLogSize, NULL, buf);
		printf("[SHADER COMPILE ERROR]: %s", buf);
		delete[] buf;
	}

	// create a program object
	this->program = glCreateProgram();
	glAttachShader(this->program, this->vertexShader);
	glAttachShader(this->program, this->pixelShader);
	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
		printf("[PROGRAM LINK ERROR]: %s", buf);
		delete[] buf;
	}
}

void ShaderObject::Apply()
{
	glUseProgram(this->program);
}

void ShaderObject::Matrix4fv(GLuint uniformLocation, float* p)
{
	glUniformMatrix4fv(uniformLocation, 1, GL_TRUE, p);
}

void ShaderObject::Vector4fv(GLuint uniformLocation, float* p)
{
	glUniform4fv(uniformLocation, 1, p);
}

GLuint ShaderObject::UniformLocation(const GLchar* uni)
{
	return glGetUniformLocation(this->program, uni);
}

void ShaderObject::BindShaders()
{

}

void ShaderObject::LoadShader(const string& fileNameVS, const string& fileNameFS)
{
	ifstream file1, file2;

	string fileName1 = fileNameVS;
	// string fileName1 = "projects//MathLib4D//Shaders//vsPhysics.glsl";
	file1.open((fileName1).c_str());
	string line1;

	if (file1.is_open())
	{
		while (file1.good())
		{
			getline(file1, line1);
			output1.append(line1 + "\n");
		}
	}
	else
	{
		cerr << "Unable to load VertexshaderObject: " << fileName1 << endl;
	}

	// string fileName2 = "projects//MathLib4D//Shaders//fsPhysics.glsl";
	string fileName2 = fileNameFS;
	file2.open((fileName2).c_str());
	string line2;

	if (file2.is_open())
	{
		while (file2.good())
		{
			getline(file2, line2);
			output2.append(line2 + "\n");
		}
	}
	else
	{
		cerr << "Unable to load FragmentshaderObject: " << fileName2 << endl;
	}
}

void ShaderObject::LoadFromFile()
{

}

ShaderObject::~ShaderObject()
{

}