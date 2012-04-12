#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Material.h"
#include "Vector3D.h"
#include "Ray.h"
#include "Collision.h"

class Primitive
{
		
public:      
	Material* Material;
	Vector3D Location;
	Primitive(void){};
    virtual Collision Intersection(Ray ray)=0;

private:
	
};
#endif