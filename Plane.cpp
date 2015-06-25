#include "Plane.h"


bool Plane::intersect(const Ray& ray1, float &prevT, HitInfo& hitInfo1)const
{

	glm::vec3 p = ray1.getstartPosition();
	glm::vec3 d = ray1.getDirection();

	float t = glm::dot(normal, (position - p)) / (glm::dot(d, normal));
	
	if (t > 0.001f && t < prevT){
		prevT = t;

		glm::vec3 pp = p + d * t;

		hitInfo1.setNormal(normal);
		hitInfo1.setVector(pp);

		return true;

	}

	return false;
}