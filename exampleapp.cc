#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include "MeshResource.h"
#include "TextureResource.h"
#include "ShaderObject.h"
#include <ctime>
#include "tinyxml2.h"
#include <string>
#include "imgui.h"
#include <cstdio> 
#include <cstdlib> 
#include <fstream>
#include "stb_image.h"

using namespace Display;

JontesProjekt::JontesProjekt()
{
}
JontesProjekt::~JontesProjekt()
{
}

bool JontesProjekt::Open()
{
	App::Open();
#pragma region keyBinds
	this->window = new Display::Window;
	window->SetSize(windowX, windowY);

	window->SetMouseMoveFunction([this](float64 x, float64 y) 
	{
		mouseX = x;
		mouseY = y;
	});

	window->SetMousePressFunction([this](int32 key, int32 state, int32) 
	{
        if (key == GLFW_MOUSE_BUTTON_LEFT && state == GLFW_PRESS)
        {
			//debugCount++;
			//// rays.clear();
			//GraphicsNode *rayNode = new GraphicsNode();
			//rayNode->Setup(1);

			//ray.start = Vector3 // Has correct start point
			//(
			//	position.x,
			//	position.y,
			//	position.z
			//);


			//rayNode->SetMesh(MeshResource::CreateRay(ray.start, ray.end));
			//rays.push_back(rayNode);
        }
        if (key == GLFW_MOUSE_BUTTON_LEFT && state == GLFW_RELEASE)
        {
            
        }
        if (key == GLFW_MOUSE_BUTTON_RIGHT && state == GLFW_PRESS)
        {
			mouseRight = true;
		}
        if (key == GLFW_MOUSE_BUTTON_RIGHT && state == GLFW_RELEASE)
        {
			mouseRight = false;
			doOnce = true;
        }
	});



	window->SetMouseScrollFunction([this](float64 x, float64 y)
    {
		translateZ += 0.07f * y;
		viewMatrix.TranslateZ(cameraInitZ + translateZ);
    });

	window->SetKeyPressFunction([this](int32 key, int32 scancode, int32 action, int32 mods) 
	{

		if (key == GLFW_KEY_W && action == GLFW_PRESS)
		{
			keyW = true;
		}
		if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		{
			keyW = false;
		}

		if (key == GLFW_KEY_S && action == GLFW_PRESS)
		{
			keyS = true;
		}
		if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		{
			keyS = false;
		}

		if (key == GLFW_KEY_A && action == GLFW_PRESS)
		{
			keyA = true;
		}
		if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		{
			keyA = false;
		}

		if (key == GLFW_KEY_D && action == GLFW_PRESS)
		{
			keyD = true;
		}
		if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		{
			keyD = false;
		}

		if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		{
			keyQ = true;
		}
		if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
		{
			keyQ = false;
		}

		if (key == GLFW_KEY_E && action == GLFW_PRESS)
		{
			keyE = true;
		}
		if (key == GLFW_KEY_E && action == GLFW_RELEASE)
		{
			keyE = false;
		}

		if (key == GLFW_KEY_F && action == GLFW_PRESS)
		{
			keyF = true;
		}
		if (key == GLFW_KEY_F && action == GLFW_RELEASE)
		{
			keyF = false;
		}

		if (key == GLFW_KEY_R && action == GLFW_PRESS)
		{
			keyR = true;
		}
		if (key == GLFW_KEY_R && action == GLFW_RELEASE)
		{
			keyR = false;
		}

		if (key == GLFW_KEY_C && action == GLFW_PRESS)
		{
			keyC = true;
		}
		if (key == GLFW_KEY_C && action == GLFW_RELEASE)
		{
			keyC = false;
		}

		if (key == GLFW_KEY_ESCAPE)
		{
			this->window->Close();
		}
	});

	if (this->window->Open())
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		return true;
	}
#pragma endregion
	return false;
}

inline
float JontesProjekt::edgeFunction(const Vec2 &a, const Vec2 &b, const Vec2 &c)
{
	return (c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]);
}



void JontesProjekt::Run()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glLineWidth(5.0f);
	glColor3f(0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	position = Vector3(0, 0, 0);


	//int width, height, numComponents;
	//unsigned char* data;
	//data = stbi_load(("first.ppm"), &width, &height, &numComponents, 3);

	//if (data == NULL)
	//	cerr << "Unable to load texture: " << endl;

	//std::ifstream is("first.ppm", std::ifstream::binary);
	//if (is)
	//{
	//	is.seekg(0, is.end);
	//	int length = is.tellg();
	//	is.seekg(0, is.beg);

	//	char *buffer = new char[length];

	//	is.read(buffer, length);

	//	int totalSize = 0;

	//	//Prepare naxHeader to be able to store data in form of casted char* to its own datatype.
	//	//The data is incremented by the size of Nax3Header datatype and converted from bytes to whatever datatypes Nax3Header stores.
	//	//This is done evertime buffer is incremented in this function.
	//	char *naxHeader = (char *)buffer;
	//	//buffer += sizeof(char);
	//	buffer += sizeof(Rgb);
	//	buffer += sizeof(Rgb);
	//	buffer += sizeof(Rgb);

	//}
	//stbi_image_free(data);



	//for (i = 0; i < size; i += 3)
	//{
	//	unsigned char tmp = data[i];
	//	
	//	data[i] = data[i + 2];
	//	data[i + 2] = tmp;
	//}

	//std::ifstream file("first.ppm");
	//if (file.is_open()) {
	//	std::string line;
	//	while (getline(file, line)) {
	//		// using printf() in all tests for consistency
	//		printf("%s", line.c_str());
	//	}
	//	file.close();
	//}

	const uint32_t w = 2;
	const uint32_t h = 2;

	int i, j;
	FILE* f = fopen("first.ppm", "rb");

	unsigned char header[11];
	fread(header, sizeof(unsigned char), 11, f);

	int size = 3 * w * h;
	Rgb *data = new Rgb[w*h];

	fread(data, sizeof(Rgb), w*h, f);
	fclose(f);

	Vec2 v0 = { 491.407, 411.407 }; //höger röd
	Vec2 v1 = { 148.593, 68.5928 }; //uppe vänster grön
	Vec2 v2 = { 148.593, 411.407 }; //nere vänster blå

	Vec2 st0 = { 1, 0 };
	Vec2 st1 = { 0, 1 };
	Vec2 st2 = { 0, 0 };

	Vec3 c0 = { 1, 0, 0 };
	Vec3 c1 = { 0, 1, 0 };
	Vec3 c2 = { 0, 0, 1 };

	FILE *fp = fopen("first1.ppm", "wb"); /* b - binary mode */
	(void)fprintf(fp, "P6\n%d %d\n255\n", h, w);
	Rgb *BIGcolor = new Rgb[w * h];
	float area = edgeFunction(v0, v1, v2);
	for (uint32_t j = 0; j < h; ++j) {
		for (uint32_t i = 0; i < w; ++i) {
			
			//Vec2 p = { i + 0.5f, j + 0.5f };
			//float w0 = edgeFunction(v1, v2, p);
			//float w1 = edgeFunction(v2, v0, p);
			//float w2 = edgeFunction(v0, v1, p);

			//if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
			//	w0 /= area;
			//	w1 /= area;
			//	w2 /= area;
			//	float r = w0 * c0[0] + w1 * c1[0] + w2 * c2[0];
			//	float g = w0 * c0[1] + w1 * c1[1] + w2 * c2[1];
			//	float b = w0 * c0[2] + w1 * c1[2] + w2 * c2[2];

			//	BIGcolor[j * w + i][0] = (unsigned char)(r * 255);
			//	BIGcolor[j * w + i][1] = (unsigned char)(g * 255);
			//	BIGcolor[j * w + i][2] = (unsigned char)(b * 255);
			//}


			BIGcolor[j * w + i][0] = data[2][0];
			BIGcolor[j * w + i][1] = data[2][1];
			BIGcolor[j * w + i][2] = data[2][2];
		}
	}
	(void)fwrite(BIGcolor, 1, w*h*3, fp);
	(void)fclose(fp);


	

	//Vec2 v0 = { 491.407, 411.407 };
	//Vec2 v1 = { 148.593, 168.5928 }; //blue, nere vänster
	//Vec2 v2 = { 148.593, 411.407 };
	////Vec2 st0 = {}
	//Vec3 c0 = { 1, 0, 0 };
	//Vec3 c1 = { 0, 1, 0 };
	//Vec3 c2 = { 0, 0, 1 };

	//const uint32_t w = 512;
	//const uint32_t h = 512;

	//Rgb *framebuffer = new Rgb[w * h];
	//memset(framebuffer, 0x0, w * h * 3);

	//float area = edgeFunction(v0, v1, v2);

	//for (uint32_t j = 0; j < h; ++j) {
	//	for (uint32_t i = 0; i < w; ++i) {
	//		Vec2 p = { i + 0.5f, j + 0.5f };
	//		float w0 = edgeFunction(v1, v2, p);
	//		float w1 = edgeFunction(v2, v0, p);
	//		float w2 = edgeFunction(v0, v1, p);
	//		if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
	//			w0 /= area;
	//			w1 /= area;
	//			w2 /= area;
	//			float r = w0 * c0[0] + w1 * c1[0] + w2 * c2[0];
	//			float g = w0 * c0[1] + w1 * c1[1] + w2 * c2[1];
	//			float b = w0 * c0[2] + w1 * c1[2] + w2 * c2[2];
	//			framebuffer[j * w + i][0] = (unsigned char)(r * 255);
	//			framebuffer[j * w + i][1] = (unsigned char)(g * 255);
	//			framebuffer[j * w + i][2] = (unsigned char)(b * 255);
	//		}
	//	}
	//}

	//std::ofstream ofs;
	//ofs.open("./raster2d.ppm");
	//ofs << "P6\n" << w << " " << h << "\n255\n";
	//ofs.write((char*)framebuffer, w * h * 3);
	//ofs.close();

	//delete[] framebuffer;

	projectionMatrix = projectionMatrix.Perspective(45.0f, windowX / windowY, 0.1f, 100.0f);



	GraphicsNode *graphicsNode = new GraphicsNode();
	graphicsNode->Setup(0);
	graphicsNode->worldTransform.SetPositionZ(-8);
	 //graphicsNode->SetMesh(MeshResource::CreateObj(0));
	graphicsNode->SetMesh(MeshResource::CreateQuad_t());
	graphicsNodes.push_back(graphicsNode);

	//for (int i = 0; i < 20; i++)
	//{
	//	cout << *(graphicsNode->GetMesh()->vertexBuffer + i) << endl;
	//}

	SoftwareRenderer rasterizer;
	rasterizer.mvpMatrix = (projectionMatrix * viewMatrix * graphicsNode->worldTransform);
	rasterizer.vertexBuffer = graphicsNode->GetMesh()->vertexBuffer;
	rasterizer.indexBuffer = graphicsNode->GetMesh()->indexBuffer;

	//Will be the same for all graphicNodes
	pointLight.pos.SetVect(0.0f, 0.0f, -4.0f, 1.0f);
	pointLight.colour.SetVect(0.8f, .1f, .1f, 1.0f);
	pointLight.intensity = 10.0f;
	float *_light = pointLight.pos.VectorToArray();
	float *_pointLightColour = pointLight.colour.VectorToArray();


	start = std::chrono::high_resolution_clock::now();
	while (this->window->IsOpen())
	{
		KeyPress();

		viewMatrix = MatrixLib4D::LookAt
		(
			viewMatrix,
			position,				
			position + direction,	
			up
		);

		mouseLeft = false;
		for (int i = 0; i < graphicsNodes.size(); i++)
		{
			GraphicsNode *tempNode = graphicsNodes[i];

			//float *_mvp = (tempNode->worldTransform * viewMatrix * projectionMatrix).MatrixToArray();
			float *_mvp = (projectionMatrix * viewMatrix * tempNode->worldTransform).MatrixToArray();
			float *_model = tempNode->worldTransform.MatrixToArray();
			float *_view = viewMatrix.MatrixToArray();
			float *_projection = projectionMatrix.MatrixToArray();
			tempNode->matRot.CopyRotationY(tempNode->worldTransform);
			float *_rotation = tempNode->matRot.MatrixToArray();

			//Draw skin
			GLuint prog = tempNode->GetShader()->program;
			
			//Variables that changes
			glUniformMatrix4fv(glGetUniformLocation(prog, "uMVP"), 1, GL_TRUE, _mvp);
			glUniformMatrix4fv(glGetUniformLocation(prog, "uModel"), 1, GL_TRUE, _model);
			glUniformMatrix4fv(glGetUniformLocation(prog, "uView"), 1, GL_TRUE, _view);
			glUniformMatrix4fv(glGetUniformLocation(prog, "uProjection"), 1, GL_TRUE, _projection);
			glUniformMatrix4fv(glGetUniformLocation(prog, "uNormalsRot"), 1, GL_TRUE, _rotation);

			//Variables that stays constant
			glUniform4fv(glGetUniformLocation(prog, "uLight"), 1, _light);
			glUniform4fv(glGetUniformLocation(prog, "uPointLightColour"), 1, _pointLightColour);
			glUniform1f(glGetUniformLocation(prog, "uPointLightIntensity"), pointLight.intensity);



			tempNode->Draw();
		}

		for (int i = 0; i < rays.size(); i++)
		{
			GraphicsNode *tempNode = rays[i];

			float *_mvp = (projectionMatrix * viewMatrix * tempNode->worldTransform).MatrixToArray();
			float *_model = tempNode->worldTransform.MatrixToArray();
			float *_view = viewMatrix.MatrixToArray();
			float *_projection = projectionMatrix.MatrixToArray();
			tempNode->matRot.CopyRotationY(tempNode->worldTransform);
			float *_rotation = tempNode->matRot.MatrixToArray();

			//Draw skin
			GLuint prog = tempNode->GetShader()->program;

			//Variables that changes
			glUniformMatrix4fv(glGetUniformLocation(prog, "uMVP"), 1, GL_TRUE, _mvp);
			glUniformMatrix4fv(glGetUniformLocation(prog, "uModel"), 1, GL_TRUE, _model);
			glUniformMatrix4fv(glGetUniformLocation(prog, "uView"), 1, GL_TRUE, _view);
			glUniformMatrix4fv(glGetUniformLocation(prog, "uProjection"), 1, GL_TRUE, _projection);
			glUniformMatrix4fv(glGetUniformLocation(prog, "uNormalsRot"), 1, GL_TRUE, _rotation);

			//Variables that stays constant
			glUniform4fv(glGetUniformLocation(prog, "uLight"), 1, _light);
			glUniform4fv(glGetUniformLocation(prog, "uPointLightColour"), 1, _pointLightColour);
			glUniform1f(glGetUniformLocation(prog, "uPointLightIntensity"), pointLight.intensity);



			tempNode->Draw();
		}
		
		// glBegin(GL_LINES);
		// glVertex3f
		// (
		// 	0,
		// 	0,
		// 	0
		// );


		inverseProjectionMatrix = inverseProjectionMatrix.Invert(projectionMatrix, projectionMatrix);
		inverseViewMatrix = inverseViewMatrix.Invert(viewMatrix, viewMatrix);
		
		testMatrixView = inverseViewMatrix * viewMatrix;
		testMatrixProj = inverseProjectionMatrix * projectionMatrix;

		float x = (2.0f * mouseX) / windowX - 1.0f;
		float y = 1.0f - (2.0f * mouseY) / windowY;
		float z = 1.0f;
		Vector4 rayClip(x, y, -1.0f, 1.0f); //NDC

		Vector4 rayEye = inverseProjectionMatrix * rayClip;
		rayEye = Vector4(rayEye.vect[0], rayEye.vect[1], -1.0f, 0.0f);

		//Invert coordinates with inverseView
		Vector4 tempRayWorld = inverseViewMatrix * rayEye;

		//Invert coordinates with only inverseProjection
		// Vector4 tempRayWorld = rayEye;

		rayWorld = Vector3(tempRayWorld.vect[0], tempRayWorld.vect[1], tempRayWorld.vect[2]);

		rayWorld = rayWorld.Normalize();

		float length = 16.0f;

		ray.end = Vector3
		(
			position.x + rayWorld.x * length,
			position.y + rayWorld.y * length,
			position.z + rayWorld.z * length
		);

		// glVertex3f
		// (
		// 	ray.end.x,
		// 	ray.end.y,
		// 	ray.end.z
		// );

		// glEnd();
		if (breaks)
		{
			int hej = 3;
		}

		DrawUI();
		this->window->SwapBuffers();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->window->Update();
		end = std::chrono::high_resolution_clock::now(); // timeStamp
		duration = end - start;
		deltaTime = duration.count();
		start = end;
	}
}

void JontesProjekt::DrawUI()
{
	this->window->SetUiRender([this]() 
	{

			ImGui::SetNextWindowSize(ImVec2(450.0f, 1200.0f), ImGuiSetCond_FirstUseEver);
			ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiSetCond_FirstUseEver);
			ImGui::Begin("asd");

			ImGui::Text("Mouse X: %f", mouseX);
			ImGui::Text("Mouse Y: %f", mouseY);
			ImGui::Text("Rays: %d", rays.size());
			ImGui::Text("deltaTime: %f", duration.count());

			ImGui::Text("RayWorld %f:%f:%f", rayWorld.x, rayWorld.y, rayWorld.z);
			ImGui::Text("Camera:");
			ImGui::Text("Position %f:%f:%f", position.x, position.y, position.z);
			ImGui::Text("Direction %f:%f:%f", direction.x, direction.y, direction.z);
			ImGui::Text("Right %f:%f:%f", right.x, right.y, right.z);
			ImGui::Text("Up %f:%f:%f", up.x, up.y, up.z);

			ImGui::Text("horizontal angle %f", horizontalAngle);
			ImGui::Text("vertical angle %f", verticalAngle);

			ImGui::Text("View Matrix:");
			for (int i = 0; i < 4; i++)
			{
				ImGui::Text("[%f][%f][%f][%f]", viewMatrix.m[i][0], viewMatrix.m[i][1], viewMatrix.m[i][2], viewMatrix.m[i][3]);
			}


			ImGui::Text("InverseView Matrix:");
			for (int i = 0; i < 4; i++)
			{
				ImGui::Text("[%f][%f][%f][%f]", inverseViewMatrix.m[i][0], inverseViewMatrix.m[i][1], inverseViewMatrix.m[i][2], inverseViewMatrix.m[i][3]);
			}


			ImGui::Text("testMatrixView Matrix:");
			for (int i = 0; i < 4; i++)
			{
				ImGui::Text("[%f][%f][%f][%f]", testMatrixView.m[i][0], testMatrixView.m[i][1], testMatrixView.m[i][2], testMatrixView.m[i][3]);
			}



			// ImGui::Text("testMatrixProj Matrix:");
			// for (int i = 0; i < 4; i++)
			// {
			// 	ImGui::Text("[%f][%f][%f][%f]", testMatrixProj.m[i][0], testMatrixProj.m[i][1], testMatrixProj.m[i][2], testMatrixProj.m[i][3]);
			// }



			ImGui::End();
	});
}


void JontesProjekt::KeyPress()
{
	if (keyQ)
	{
		position = position - up * cameraSpeed;
	}

	if (keyE)
	{
		position = position + up * cameraSpeed;
	}

	if (keyW)
	{
		position = position + direction * cameraSpeed;
	}

	if (keyA)
	{
		position = position - right * cameraSpeed;
	}

	if (keyS)
	{
		position = position - direction * cameraSpeed;
	}

	if (keyD)
	{
		position = position + right * cameraSpeed;
	}

	if (keyF)
	{
		breaks = true;
		graphicsNodes[0]->worldTransform = graphicsNodes[0]->worldTransform * graphicsNodes[0]->worldTransform.RotationY(4.0f);
	}

	if (keyR)
	{
		graphicsNodes[0]->worldTransform = graphicsNodes[0]->worldTransform * graphicsNodes[0]->worldTransform.RotationY(-4.0f);
	}

	if(mouseRight)
	{

		if (doOnce)
		{
			newX = mouseX;
			newY = mouseY;
			doOnce = false;
		}

		dX = mouseX - newX; //if +, increase angle, if - decrease angle
		dY = mouseY - newY;
		if (dX > 0)
		{
			horizontalAngle -= mouseSpeed * dX;
		}
		else if (dX < 0) 
		{
			horizontalAngle -= mouseSpeed * dX;
		}

		if (dY > 0)
		{
			verticalAngle -= mouseSpeed * dY;
		}
		else if (dY < 0) 
		{
			verticalAngle -= mouseSpeed * dY;
		}

		// horizontalAngle = 2.0f;
		// verticalAngle = -1.0f;


		newX = mouseX;
		newY = mouseY;

		direction = Vector3
		(
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
		);

		right = Vector3
		(
			sin(horizontalAngle - 3.14159f/2.0f),
			0,
			cos(horizontalAngle - 3.14159f/2.0f)
		);

		up = Vector3::Cross(right, direction);
	}
}