#pragma once
class base
{
public:
	virtual void draw() = 0;

protected:
	float* vertices;
	float* colours;
	int* index;
	glm::mat4 matrix;
	/*matrix m;*/
	
};
