#include "Shape.h"

const Material& Shape::getMaterial(){
	return material;
}
void Shape::setMaterial(const Material& shapeMaterial){
	material = shapeMaterial;
}

