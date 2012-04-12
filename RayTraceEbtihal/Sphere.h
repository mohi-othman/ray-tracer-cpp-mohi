#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"
#include "Material.h"

class Sphere :
	public Primitive
{
public:	
	float Radius;
	
	Sphere(Vector3D Center, double size) 
	{
		Location = Center;
		Radius = size;
	} ;
		
	Collision Intersection(Ray ray);
	Vector3D GetNormal(Vector3D point);
};

#endif