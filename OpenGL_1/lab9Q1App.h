#pragma once
#include "SOF.h"

class Lab9Q1App : public SOF::App
{

	// this app will render a cube
	SOF::ShaderProgram *shader;
	SOF::Geometry *cubeGeom;

	GLfloat delay = 0;
	GLint axis = 1;
	GLfloat  theta[3] = { 0.0, 0.0, 0.0 };
	GLboolean drawLines = false;
	GLboolean colourFaces = false;
	GLboolean pointToggle = false;



public:
	virtual void Draw();
	virtual void Init();
	virtual void Update(float deltaT);
	virtual void KeyCallback(GLFWwindow*, int, int, int, int);
	virtual void MouseButtonCallback(GLFWwindow*, int, int, int);
};