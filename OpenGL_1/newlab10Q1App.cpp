#include "stdafx.h"
#include "newlab10Q1App.h"
#include "CubeLab10.h"
#include "pyramid.h"
#include <string>
#include <random>

GLint count = 0;									//Set integer for OpenGL items to 0
GLint offset = 50;
GLboolean cubeSpawn;
GLboolean pyraSpawn;


void NewLab10Q1App::Init()
{
	// build a set of 6 cubes
	for (int i = 0; i < 50; i++)
	{
		CubeLab10 *cube = new CubeLab10();
		cubes.push_back(cube);
	}
	/*for (int j = 0; j < 20; j++) {
		cubes[j]->SetTranslate(glm::vec3(float(rand() / float((RAND_MAX)) + 1), float(rand() / float((RAND_MAX)) + 1), 0));
		cubes[j]->SetScale(glm::vec3(float(rand() / float((RAND_MAX)) + 1), float(rand() / float((RAND_MAX)) + 1), float(rand() / float((RAND_MAX)) + 1)));
	}*/
	for (int j = 0; j < 50; j++)
	{
		pyramid *pyra = new pyramid();
		pyras.push_back(pyra);
	}
	cubeSpawn = true;
	pyraSpawn = false;
	// set up the relative shapes - use matrix tranforms internally
	// model matrix - body cube
	// This sits at the origin, so we just need to sort out its size and aspect ratio
	//cubes[0]->SetScale(glm::vec3(1.0, 1.0, 0.6));
	//cubes[0]->setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));

	// some render states
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

// responses to the passing of time. Called with before each draw()
void NewLab10Q1App::Update(float deltaT)
{
	if (delay >= 0.01f)
	{
		theta[axis] += 0.5f;

		if (theta[axis] > 360.0) {
			theta[axis] -= 360.0;
		}
		delay = 0.0f;
	}
	else
		delay += deltaT;
	
}

void NewLab10Q1App::KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	if (key == GLFW_KEY_A)
		cameraXAngle += 5;
	if (key == GLFW_KEY_S)
		cameraYAngle += 5;
	if (key == GLFW_KEY_D)
		cameraZAngle += 5;
	if (key == GLFW_KEY_Z)
		cameraXAngle -= 5;
	if (key == GLFW_KEY_X)
		cameraYAngle -= 5;
	if (key == GLFW_KEY_C)
		cameraZAngle -= 5;
													//Add a key to zoom in out, or move around the scene
	if (key == GLFW_KEY_U)
		axis = 0;
	if (key == GLFW_KEY_I)
		axis = 1;
	if (key == GLFW_KEY_O)
		axis = 2;

	//if (key == GLFW_KEY_P)
		//cubeSpawn = !cubeSpawn;
		//pyraSpawn = !pyraSpawn;//Selects object spawn
		//cubeSpawn = true
	/*if (key == GLFW_KEY_L)
		pyraSpawn = true;
		cubeSpawn = false;*/
		//cubeSpawn = false;
	if (key == GLFW_KEY_M)
		interpolateColour = !interpolateColour;
	//Key N to toggle colour interpolation
	// set interpolateColour to false when pressed
	if (key == GLFW_KEY_N)
		interpolateColour = false;
	//Separate interpolate for Square, green, Pyramid red
	/*if (key == GLFW_KEY_N)
		cubes[0]->setColor(interpolate);
		pyras[0]->setColor(interpolate);*/
	//Change colour of squares from interpolated to same colour
	//Boolean variables set to true, e.g keypress P sets cube to true in order to be duplicated
		
}


void NewLab10Q1App::MouseButtonCallback(GLFWwindow* window, int button, int scanCode, int action)
{
	////while (cubeSpawn) {  //FIX SPAWN LOGIC, CHOOSE ONE OBJECT AT A TIME PER KEY OR CHOOSE BOTH WITH ANOTHER KEY (K)
	//	if (button == GLFW_MOUSE_BUTTON_LEFT && scanCode == GLFW_PRESS)									//Only for a key click, not click and release
	//	{
	//		if (count < 50 && cubeSpawn) {																			//Limit squares to 50, prevent a crash error
	//			count++;																				//Increment count for every new cube drawn
	//			CubeLab10* cube = new CubeLab10;
	//			cube->SetTranslate(glm::vec3(count, count, float(rand() % (21 - 10) + 10)));			//Translate x and y by the count variable
	//			cube->SetScale(glm::vec3(float(rand() / float((RAND_MAX)) + 1), float(rand() / float((RAND_MAX)) + 1), float(rand() / float((RAND_MAX)) + 1)));		//Set a random size between 0 and 1
	//			//Orientation
	//			cube->SetXRotation((float(rand() % 360 + 1)));
	//			cube->SetYRotation((float(rand() % 360 + 1))); //RAND BETWEEN 0 AND 360 DEGREES
	//			cube->SetZRotation((float(rand() % 360 + 1)));
	//			cubes.push_back(cube);								//Left mouse button to add object to screen
	//			pyraSpawn = false;
	//			std::cout << "There are : " << count << "squares" << std::endl;
	//			
	//		}

	//		else if (count < 50 && pyraSpawn) {
	//			count++;
	//			pyramid* pyra = new pyramid();
	//			pyra->SetTranslate(glm::vec3(count, count, float(rand() % (21 - 10) + 10)));			//Translate x and y by the count variable
	//			pyra->SetScale(glm::vec3(float(rand() / float((RAND_MAX)) + 1), float(rand() / float((RAND_MAX)) + 1), float(rand() / float((RAND_MAX)) + 1)));		//Set a random size between 0 and 1
	//			pyra->SetXRotation((float(rand() % 360 + 1)));
	//			pyra->SetYRotation((float(rand() % 360 + 1))); //RAND BETWEEN 0 AND 360 DEGREES
	//			pyra->SetZRotation((float(rand() % 360 + 1)));
	//			pyras.push_back(pyra);
	//			cubeSpawn = false;
	//			std::cout << "There are : " << count << "pyramids" << std::endl;
	//		}
	//	}
	////}

	while (cubeSpawn == true)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && scanCode == GLFW_PRESS)									//Only for a key click, not click and release
		{
			if (count < 50) {																			//Limit squares to 50, prevent a crash error
				count++;																				//Increment count for every new cube drawn
				CubeLab10* cube = new CubeLab10();
				cube->SetTranslate(glm::vec3(count, count, float(rand() % (21 - 10) + 10)));			//Translate x and y by the count variable
				cube->SetScale(glm::vec3(float(rand() / float((RAND_MAX)) + 1), float(rand() / float((RAND_MAX)) + 1), float(rand() / float((RAND_MAX)) + 1)));		//Set a random size between 0 and 1
				cube->SetXRotation((float(rand() % 360 + 1)));
				cube->SetYRotation((float(rand() % 360 + 1))); //RAND BETWEEN 0 AND 360 DEGREES
				cube->SetZRotation((float(rand() % 360 + 1)));
				cubes.push_back(cube);
				cubeSpawn = false;
				pyraSpawn = true;
				std::cout << count << " : Square(s) Spawned" << std::endl;
			}
			

		}
		break;
	}
	
	while (pyraSpawn == true)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && scanCode == GLFW_PRESS)									//Only for a key click, not click and release
		{
			if (count < 50) {																			//Limit squares to 50, prevent a crash error
				count++;																				//Increment count for every new cube drawn
				pyramid* pyra = new pyramid();
				pyra->SetTranslate(glm::vec3(count, count, float(rand() % (21 - 10) + 10)));			//Translate x and y by the count variable
				pyra->SetScale(glm::vec3(float(rand() / float((RAND_MAX)) + 1), float(rand() / float((RAND_MAX)) + 1), float(rand() / float((RAND_MAX)) + 1)));		//Set a random size between 0 and 1
				pyra->SetXRotation((float(rand() % 360 + 1)));
				pyra->SetYRotation((float(rand() % 360 + 1))); //RAND BETWEEN 0 AND 360 DEGREES
				pyra->SetZRotation((float(rand() % 360 + 1)));
				pyras.push_back(pyra);
				pyraSpawn = false;
				cubeSpawn = true;
				std::cout << count << " : Pyramid(s) Spawned"  << std::endl;
			}
			
			
		}
		break;
		
	}
	
	
	if (button == GLFW_MOUSE_BUTTON_RIGHT && scanCode == GLFW_PRESS) {											//Differentiate between left and right click
		if (count > 0 ) { //if count > 0 && cubeSpawn == true, remove only selected object
			count--;
			cubes[count]->SetScale(glm::vec3(0.0f, 0.0f, 0.0f));							//Set current square count to a size of 0
			cubes.pop_back();																//Right to remove object off screen, pop it from stack
			std::cout << "There are : " << count << "squares" << std::endl;
			pyras[count]->SetScale(glm::vec3(0.0f, 0.0f, 0.0f));
			pyras.pop_back();
			std::cout << "There are : " << count << "pyramids" << std::endl;
			
		}
		//else if (count > 0 /*&& pyraSpawn*/) {
		//	
		// Removes selected shape
		// pyras[count]->SetScale(glm::vec3(0.0f, 0.0f, 0.0f));
		//pyras.pop_back();
		//std::cout << "There are : " << count << "pyramids" << std::endl;
		//}
		
	}
		
}


void NewLab10Q1App::Draw()
{
	//// camera and projection 
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 40.0f);
	cameraDir[0] = glm::radians(cameraXAngle);
	cameraDir[1] = glm::radians(cameraYAngle);
	cameraDir[2] = glm::radians(cameraZAngle);
	glm::mat4 view = glm::lookAt(cameraPos, cameraDir, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj = glm::perspective(glm::radians(70.0f), (float)SOF::Window::GetHeight() / SOF::Window::GetWidth(), 0.1f, 1000.0f);

	// model matrix (rotate the whole thing)
	glm::mat4 model = glm::mat4();
	model = glm::translate(model, glm::vec3(0, 0, 0));
	model = glm::scale(model, glm::vec3(1.5, 1.5, 1.5));
	model = glm::rotate(model, (float)glm::radians(theta[0]), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, (float)glm::radians(theta[1]), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, (float)glm::radians(theta[2]), glm::vec3(0.0f, 0.0f, 1.0f));
	cubes[0]->SetBaseTransform(model);
	pyras[0]->SetBaseTransform(model);
	
	
	// draw the cubes
	for (auto cube : cubes)
		cube->Draw(view, proj);
		for (auto cube : cubes) {
			if (interpolateColour) {
				cube->setColor(interpolate);
				cube->Draw(view, proj);
			}
		}
		
		
	

	//draw the pyramids
	for (auto pyra : pyras)						
		pyra->Draw(view, proj);								//Draw pyramids
		for (auto pyra : pyras) {							//Nested for loop 
			if (interpolateColour) {						//Checks for colour key press
				pyra->setColor(interpolate);				//Adjusts the colour to the vec4 RGB values
				pyra->Draw(view, proj);						//Draws the selected shape
			}
			
			
		}
		
}
