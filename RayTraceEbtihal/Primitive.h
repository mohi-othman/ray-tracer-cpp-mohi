//Base 3D primitive class.

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Material.h"
#include "Vector3D.h"
#include "Ray.h"
#include "Collision.h"

class Primitive
{
		
public:      
	Material* Material;	//Material of the object
	Vector3D Location;	//Location of the center of the object
	Primitive(void){};	//Default constructor

	//Function to test for collision with a ray
    virtual Collision Intersection(Ray ray)=0;
	
};
#endif