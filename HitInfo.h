#pragma once

#include <glm\vec3.hpp>

class HitInfo
{
public:
	HitInfo(){}
	~HitInfo(){}

	void setNormal(glm::vec3);
	void setVector(glm::vec3);

	glm::vec3 getNormal();
	glm::vec3 getVector();

private:

	glm::vec3 normal;
	glm::vec3 vector;

};

