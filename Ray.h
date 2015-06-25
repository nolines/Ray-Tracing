#pragma once

#include <glm/vec3.hpp>

class Ray
{
public:
	Ray() : startPosition(0.0f), direction(0.0f, 0.0f, -1.0f){}
	~Ray(){}

	void Ray::setstartPosition(const glm::vec3& pos){
		startPosition = pos;
	}

	void Ray::setDirection(const glm::vec3& dir	){
		direction = dir;
	}

	const glm::vec3& Ray::getDirection()const{
		return direction;
	}

	const glm::vec3& Ray::getstartPosition()const{
		return startPosition;
	}

private:
	glm::vec3 startPosition;
	glm::vec3 direction;
};
