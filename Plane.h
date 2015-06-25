#pragma once

#include "Shape.h"
#include <glm\glm.hpp>

class Plane : public Shape
{
public:
	Plane(){
	}
	~Plane(){}

	void setPosition(glm::vec3 pos){ position = pos; }
	glm::vec3 getPosition(){ return position; }
	void setNormal(glm::vec3 norm){ normal = norm; }
	glm::vec3 getNormal(){ return normal; }


	bool intersect(const Ray&, float&, HitInfo&)const override;

private:
	glm::vec3 position;
	glm::vec3 normal;
};

