//Class for sphere primitive, dervied from the base Primitive class.

#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"
#include "Material.h"

class Sphere :
	public Primitive
{
public:	
	float Radius;	//Radius of the sphere
	
	Sphere(Vector3D Center, float size) //Main constructor
	{
		Location = Center;
		Radius = size;
	} ;
		
	Collision Intersection(Ray ray);
	Vector3D GetNormal(Vector3D point);	//Retrieves normal at point.
};

#endif