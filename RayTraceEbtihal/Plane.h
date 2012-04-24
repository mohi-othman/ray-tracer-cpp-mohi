//Class for plane primitive, dervied from the base Primitive class.

#ifndef PLANE_H
#define PLANE_H

#include "primitive.h"
class Plane :
	public Primitive
{
public:
	float Distance;		//Distance from origin
    Vector3D Normal;	//Normal of the plane

	Plane(float distance, Vector3D normal)	//Main constructor
	{			
		normal.Normalize();
		Normal = normal;
		Distance = distance;				
	}
	
	Collision Intersection(Ray ray);
	
	Vector3D GetNormal();	//retrieves normal
};

#endif