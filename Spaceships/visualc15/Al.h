#pragma once
#include "../Rectangle.h"
#include "../GlutApp.h"
#include "../RgbImage.h"
#include "../TexRect.hpp"

class Al : public ucm::Rectangle
{
public:

	GLuint al;
	TexRect* test;
	float x;
	float y;
	float h;
	float w;

	Al(float x, float y, float h, float w) {

		
		GLuint al = loadTexture("..\\al.bmp");
		this->x = x;
		this->y = y;
		this->h = h;
		this->w = w;
		test = new TexRect(x, y, h, w);

		
	}
	GLuint loadTexture(const char *filename) {
		GLuint texture_id;
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glShadeModel(GL_FLAT);
		glEnable(GL_DEPTH_TEST);

		RgbImage theTexMap(filename);

		// Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
		//    Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );


		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);





		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(),
			GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());

		return texture_id;

	}

};
