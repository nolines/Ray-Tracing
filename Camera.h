#pragma once

#include <glm/glm.hpp>

#define HEIGHT 480
#define WIDTH 640

struct pixel
{
	unsigned char r, g, b;
};

class Camera
{
	
public:
	
	~Camera(){}
	Camera();

	void setVector(glm::vec3);
	glm::vec3 calculateDirection(int,int);

	glm::vec3 getVector();
	pixel* getBuffer();

private:
	pixel* buffer;
	glm::vec3 position;
	
};

