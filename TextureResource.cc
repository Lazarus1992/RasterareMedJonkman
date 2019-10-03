#include "config.h"
#include "TextureResource.h"
#include <iostream>
#include "string.h"
#include "stb_image.h"

using namespace std;
TextureResource::TextureResource()
{


}

void TextureResource::Bind(const string& fileName, int textureCount)
{
	int width, height, numComponents;
	unsigned char* data;
	data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);


	if (data == NULL)
		cerr << "Unable to load texture: " << endl;
	switch (textureCount)
	{
		case 0:
			glGenTextures(1, &texArray[0]);
			glBindTexture(GL_TEXTURE_2D, texArray[0]);
			break;
		case 1:
			glGenTextures(1, &texArray[1]);
			glBindTexture(GL_TEXTURE_2D, texArray[1]);
			break;
		case 2:
			glGenTextures(1, &texArray[2]);
			glBindTexture(GL_TEXTURE_2D, texArray[2]);
			break;
		default:
			break;
	}
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}


TextureResource::~TextureResource()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
