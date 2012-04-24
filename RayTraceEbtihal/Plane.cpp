#include "Plane.h"

//Formula from "Ray Tracing from the Ground Up"

Collision Plane::Intersection(Ray ray)
{	
	float d = Normal * ray.Direction;
    if (d != 0)
    {
        float dist = -((Normal * ray.Origin) + Distance) / d;
		
        if (dist > 0)
        {
            Vector3D hitPoint = ray.Origin + (dist * ray.Direction);
            return Collision(true, false, this, dist, GetNormal(), hitPoint);
        }
    }
    return Collision(false);
}

Vector3D Plane::GetNormal()
{
	return Normal;
}