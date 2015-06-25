#include "Light.h"

void Light::setPosition(glm::vec3 lightPosition){
	position = lightPosition;
}
void Light::setColor(glm::vec3 lightColor){
	color = lightColor;
}
void Light::setAmbiant(glm::vec3 lightambiant){
	ambiant = lightambiant;
}
glm::vec3 Light::getPosition(){
	return position;
}
glm::vec3 Light::getColor(){
	return color;
}
glm::vec3 Light::getAmbiant(){
	return ambiant;
}
glm::vec3 Light::PhongShading(Ray ray1,HitInfo hitInfo1, Material mat1)
{
	glm::vec3 lightVector;
	lightVector = glm::normalize(position - hitInfo1.getVector());
	float angle = glm::dot(lightVector, hitInfo1.getNormal());
	glm::vec3 diffuseColor = angle * mat1.getColorDiffused() * color;

	glm::vec3 eyeVector = glm::normalize(ray1.getstartPosition() - hitInfo1.getVector());
	glm::vec3 reflectionVector = (2 * (glm::dot(lightVector, hitInfo1.getNormal())) * hitInfo1.getNormal()) - lightVector;

	float intensityAngle =glm::pow(glm::dot(eyeVector, reflectionVector),32);
	glm::vec3 specularColor = intensityAngle * mat1.getShineness() * mat1.getColorSpeculer() * mat1.getColorDiffused();

	glm::vec3 ambientColor = ambiant * mat1.getColorDiffused();
	return (ambientColor + diffuseColor + specularColor);


}