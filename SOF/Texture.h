#pragma once
#include "stdafx.h"
#include <soil2.h>

namespace SOF
{
	class Texture
	{

	protected:
		GLuint* textureObject;
		int width, height;
		int numText = 1;

		
	public:
		Texture(const std::string &fileName); // constructor, load from file
		Texture(int nText); // constructor with number of texture objects to use
		Texture() {};
	

		void loadTexture(int num, const std::string &fileName);
		GLuint GetObject() const { return GetObject(0); }
		GLuint GetObject(int num) const { return textureObject[num]; }
		int GetWidth() const { return width; }
		int GetHeight() const { return height;  }
	};
}