#include <GL/glew.h>
#include <IL/il.h>

#include "Texture.h"

namespace gr = framework::graphics;

using namespace gr;

Texture gr::load_texture(string filename)
{
	Texture temp;

	GLuint image_id;

	ilGenImages(1, &image_id);
	ilBindImage(image_id);

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	if (!ilLoadImage((ILstring) filename.c_str()))
	{
		printf("Error loading image %s\n", filename);
		exit(-1);
	}

	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

	glGenTextures(1, &temp.texture_id);
	glBindTexture(GL_TEXTURE_2D, temp.texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2.0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, ilGetInteger(IL_IMAGE_WIDTH), 
												  ilGetInteger(IL_IMAGE_HEIGHT), 
												  0, 
												  GL_RGBA, 
												  GL_UNSIGNED_BYTE, 
												  ilGetData());

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	ilDeleteImages(1, &image_id);
	ilBindImage(0);

	return temp;
}
