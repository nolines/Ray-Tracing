#pragma once
#include <glm\glm.hpp>

class Material
{
public:
	Material(){}
	~Material(){}

	void setColorDiffused(glm::vec3);
	void setColorSpeculer(glm::vec3);
	void setShineness(float);

	glm::vec3 getColorDiffused();
	glm::vec3 getColorSpeculer();
	float getShineness();


private:

	glm::vec3 colorDiffused;
	glm::vec3 colorSpeculer;
	float shineness;

};
