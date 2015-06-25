#include "Sphere.h"

void Sphere::setPosition(glm::vec3 vec1){
	position = vec1;
}

glm::vec3 Sphere::getPosition(){
	return position;
}
float Sphere::getRadius(){
	return radius;
}

bool Sphere::intersect(const Ray& ray , float &prevT, HitInfo &hitInfo)const
{
	glm::vec3 p = ray.getstartPosition();
	glm::vec3 c = position;
	glm::vec3 d = ray.getDirection();

	float a = glm::dot(d, d);
	float b = 2.0f * (glm::dot(d, (p - c)));
	float cc = glm::dot((p-c),(p-c)) - (radius * radius);

	float delta = ( b * b ) - ( 4.0f * a * cc );

	if ( delta > 0.0f){

		float t = (-b - glm::sqrt(delta)) / (2.0f * a);
		
		if ( t > 0.001f && t < prevT){
			prevT = t;

			glm::vec3 pp = p + d * t;
			glm::vec3 norm = glm::normalize(pp - c);
	
			hitInfo.setNormal(norm);
			hitInfo.setVector(pp);

			return true;

		}

		t = (-b + glm::sqrt(delta)) / (2.0f * a);

		if (t > 0.001f && t < prevT){
			prevT = t;

			glm::vec3 pp = p + d * t;
			glm::vec3 norm = glm::normalize(pp - c);

			
			hitInfo.setNormal(norm);
			hitInfo.setVector(pp);

			return true;

		}
	}

	return false;

}