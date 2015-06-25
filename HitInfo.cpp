#include "HitInfo.h"


void HitInfo::setNormal(glm::vec3 norm){

	normal = norm;

}
void HitInfo::setVector(glm::vec3 vec){

	vector = vec;

}

glm::vec3 HitInfo::getNormal(){

	return normal;

}
glm::vec3 HitInfo::getVector(){

	return vector;
}