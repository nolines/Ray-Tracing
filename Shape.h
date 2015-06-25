#pragma once
#include "Material.h"
#include "Ray.h"
#include "HitInfo.h"


class Shape
{
public:
	Shape(){}
	virtual ~Shape(){}

	virtual bool intersect(const Ray&, float&,HitInfo&)const = 0;
	const Material& getMaterial();
	void setMaterial(const Material& mat);

private:
	Material material;

};