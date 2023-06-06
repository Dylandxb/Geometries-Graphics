#include "stdafx.h"
#include "lab9Q1App.h"
#include <random>


void Lab9Q1App::Init()
{
	shader = new SOF::ShaderProgram("shaders/lab09_vertex-shader.glsl", "shaders/lab09_fragment-shader.glsl");
	
	// make a tetrahedron with a different color at each vertex
	int nVertex = 6 * 2 * 3; // 6 faces * 2 triangles * 3 vertices each	
	cubeGeom = new SOF::Geometry(nVertex);
	// we need three sorts of data
	// the vertex locations
	glm::vec4 vertexPositions[] = {

		glm::vec4(-0.5, -0.5,  0.5, 1.0), //Bottom left
		glm::vec4(-0.5, 0.5, 0.5, 1.0),		//Left top front
		glm::vec4(0.5, 0.5, 0.5, 1.0),			//Right top front
		glm::vec4(0.5, -0.5, 0.5, 1.0),		//Right bottom front
		glm::vec4(-0.5, -0.5, -0.5, 1.0),		//Left bottom back
		glm::vec4(-0.5, 0.5, -0.5, 1.0),		//Left top back
		glm::vec4(0.5, 0.5, -0.5, 1.0),		//Right top back
		glm::vec4(0.5, -0.5, -0.5, 1.0)		//Right bottom back
	
		//put another 7 points here.
		// order: left-bottom-front (given to you), left-top-front, right-top-front, 
		// right-bottom-front, left-bottom-back, left-top-back, right-top-back, 
		// right-bottom-back
		// note that while X goes left - right and Y goes bottom - top (increasing values)
		// Z goes far - near.
		// We call this a "right hand coordinate system"
		// the final 1.0 ensures that this is treated as a homogeneous coordinate

	};
	// the corresponding colours
	glm::vec4 vertexColors[] = {
		glm::vec4(0.0, 0.0, 0.0, 1.0),  // black
	
		glm::vec4(1.0,0.0,0.0,1.0),		//red
		glm::vec4(1.0,1.0,0.0,1.0),		//yellow
		glm::vec4(0.0,1.0,0.0,1.0),		//green
		glm::vec4(0.0,0.0,1.0,1.0),		//blue
		glm::vec4(0.5,0.0,1.0,1.0),		//magneta
		glm::vec4(1.0,1.0,1.0,1.0),		//white
		glm::vec4(0.0,1.0,1.0,1.0),		//cyan
		// another 7 colour here.
		// order: red (given to you), yellow, green, blue, magenta, white, cyan
		// all these colours are combinations of 1s and 0s!
		// the channels are (in order) Red, Green, Blue.
		// final 1.0 as above. 
		
	};
	// the ordering of the vertexes 
	// this states how the vertexes are connected and is so tought setting up, I'll give you...
	int triangles[] = { 0,1,2, 0,2,3, 4,5,6, 4,6,7, 0,1,5, 0,5,4, 1,2,6, 1,6,5, 2,3,7, 2,7,6, 3,0,4, 3,4,7 };

	// create a list of vertexes, sorted into the correct triangles
	std::vector<glm::vec4> vertexPos;
	std::vector<glm::vec4> vertexColor;
	for (int i = 0; i < nVertex; i++)
	{
		vertexPos.push_back(vertexPositions[triangles[i]]);
		vertexColor.push_back(vertexColors[triangles[i]]);
	}
	// give the vertexes and shader to the tetrahedron object
	cubeGeom->AddAttribute(vertexPos, "vertexPos");
	cubeGeom->AddAttribute(vertexColor, "vertexColor");
	cubeGeom->Finalize(shader);

	shader->Use(); // enable the shader

	//shader->SetUniformVec4("fixedColor", glm::vec4(0.0, 1.0, 0.0, 1.0));				//Sets the shader to a fixed color of red

	// some render states
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

// processes keyboard events
void Lab9Q1App::KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	
	if (key == GLFW_KEY_A)
		axis = 0;
	if (key == GLFW_KEY_S)
		axis = 1;
	if (key == GLFW_KEY_D)
		axis = 2;
	if (key == GLFW_KEY_1)				
		drawLines = true;									//drawLines is a member variable initialized in the .h file, it is of type GLboolean. Set to true when key pressed
	if (key == GLFW_KEY_K)									//Key k turns rendered faces on/off
		colourFaces = true;
	if (key == GLFW_KEY_J)									//Key j turns the vertex points on/off
		pointToggle = true;
}


// processes keyboard events
void Lab9Q1App::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{

}


// responses to the passing of time. Called with before each draw()
void Lab9Q1App::Update(float deltaT)
{
	if (delay >= 0.02f)
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




void Lab9Q1App::Draw()
{
	//  view and projection matrices
	glm::mat4 view = glm::lookAt(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 proj = glm::perspective(glm::radians(70.0f), 1.0f, 0.01f, 100.0f);

	glm::mat4 vpm = proj * view;
	shader->SetUniformMat4("vpm", vpm); // set the view-projection matrix uniform in the shader program

	// model matrix
	glm::mat4 model = glm::mat4();
	model = glm::translate(model, glm::vec3(0, 0, 0));
	model = glm::scale(model, glm::vec3(1.5, 1.5, 1.5));
	model = glm::rotate(model, (float)glm::radians(theta[0]), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, (float)glm::radians(theta[1]), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, (float)glm::radians(theta[2]), glm::vec3(0.0f, 0.0f, 1.0f));

	shader->SetUniformMat4("mdm", model); // set the model matrix uniform in the shader program
	//OpenGL must draw update each time, cannot backtrack
	//draw the planes
	if (drawLines) {										//If this is true then it sets the fixed color to "on"
		shader->SetUniformInt("useFixedColor", 1);			//useFixed color changes the frag ment colour to the ficed colour in the header file
		cubeGeom->DrawLines();								//It then draws all the line as green
		shader->SetUniformVec4("fixedColor", glm::vec4(0.0, 1.0, 0.0, 1.0));
		shader->SetUniformInt("useFixedColor", 0);
	}
	if (colourFaces) {										//Toggle the rendering of colour on each face of the cube
		shader->SetUniformInt("useFixedColor", 1);
		cubeGeom->DrawPrimitives();							
		shader->SetUniformVec4("fixedColor", glm::vec4(1.0, 0.0, 0.0, 1.0));		//Change colour of faces to red
		shader->SetUniformInt("useFixedColor", 0);
	}

	if (pointToggle) {
		shader->SetUniformInt("useFixedColor", 1);
		cubeGeom->DrawPoints(10.0f);						//Sets size of pixels to 10, of type GLfloat
		shader->SetUniformInt("useFixedColor", 0);
	}
}

