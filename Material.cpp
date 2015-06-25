
#include "Material.h"

void Material::setColorDiffused(glm::vec3 colorDiff){
	colorDiffused = colorDiff;
}

void Material::setColorSpeculer(glm::vec3 colorSpec){
	colorSpeculer = colorSpec;
}
void Material::setShineness(float shine){
	shineness = shine;
}


glm::vec3 Material::getColorDiffused(){
	return colorDiffused;
}
glm::vec3 Material::getColorSpeculer(){
	return colorSpeculer;
}
float Material::getShineness(){
	return shineness;
}