// Example2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SOF.h"
#include "newlab10Q1App.h"

int main()
{
	NewLab10Q1App *app = new NewLab10Q1App();
	SOF::Window::CreateWindow(768, 768, "Assignment Q2", app);   //width and height of window
	SOF::Window::SetBackground(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	SOF::Window::Run();

    return 0;
}

