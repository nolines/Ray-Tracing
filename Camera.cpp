#include "Camera.h"


pixel* Camera::getBuffer(){
	return buffer;
}
Camera::Camera(){
	buffer = new pixel[WIDTH*HEIGHT];
	position.x = 0;
	position.y = 0;
	position.z = 10;
}

void Camera::setVector(glm::vec3 h){
	Camera::position =  h;
}

glm::vec3 Camera::getVector(){
	return position;
}

glm::vec3 Camera::calculateDirection(int i, int j)
{
	
	
	float fovy = glm::radians(45.0f);
	
	float tany = glm::tan(fovy * 0.5f);
	float tanx = tany * (float(WIDTH) / HEIGHT);

	float alpha = tanx * ((j - (WIDTH * 0.5f)) / (WIDTH * 0.5f));
	float beta = tany * ((i - HEIGHT*0.5f) / (HEIGHT*0.5f));

	glm::vec3 z = glm::normalize(position);
	glm::vec3 yy;
	yy.x = 0.0f;
	yy.y = 1.0f;
	yy.z = 0.0f;
	glm::vec3 x = glm::normalize(glm::cross(yy, z));
	glm::vec3 y = glm::cross(z,	x);

	glm::vec3 dir = glm::normalize((alpha * x) + (beta * y) - z);
		
	return dir;
}
