#include "Shape.h"
#include <glm\vec3.hpp>

class Sphere : public Shape
{
public:
	Sphere(){}
	~Sphere(){}

	void setPosition(glm::vec3 );
	void setRadius(float r){ radius = r; }

	glm::vec3 getPosition();
	float getRadius();

	bool intersect(const Ray&, float&, HitInfo&)const override;

private:
	glm::vec3 position;
	float radius;
};

