#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "HitInfo.h"
#include "Material.h"
#include "Ray.h"

class Light
{
public:
	Light();
	~Light();

	void setPosition(glm::vec3 );
	void setColor(glm::vec3 );
	void setAmbiant(glm::vec3);
	glm::vec3 PhongShading(Ray,HitInfo,Material);


	glm::vec3 getPosition();
	glm::vec3 getColor();
	glm::vec3 getAmbiant();

private:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 ambiant;
};

inline Light::Light()
{
	position.x = 0;
	position.y = 10;
	position.z = 10;
}

inline Light::~Light()
{
}