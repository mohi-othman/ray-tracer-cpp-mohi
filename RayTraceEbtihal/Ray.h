//Class to define a ray
#ifndef RAY_H
#define RAY_H

#include "Vector3D.h"

class Ray
{
public:
	struct 
	{
		Vector3D Origin;	//Coordinate of origin point of the ray
		Vector3D Direction;	//Direction of the ray
	};
		
    Ray(Vector3D origin, Vector3D direction)
	{
		direction.Normalize();
		Origin = origin;
		Direction = direction;
	};
};

#endif