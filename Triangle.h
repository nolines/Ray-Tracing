#include "Shape.h"
#include <glm\vec3.hpp>

class Triangle : public Shape
{
public:
	Triangle(){}
	~Triangle(){}

	void setPosition(glm::vec3);

	glm::vec3 getPosition();
	float getRadius();

	bool intersect(const Ray&, float&, HitInfo&)const override;

private:
	glm::vec3 position;
	float radius;
};

