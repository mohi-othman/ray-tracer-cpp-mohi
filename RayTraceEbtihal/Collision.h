//Class used to store data on collisions to be passed between functions

#ifndef COLLISION_H
#define COLLISION_H

#include "Primitive.h"
#include "Vector3D.h"
class Primitive;

class Collision
{
public:	
	bool IsCollision;		//Has a collision occured?
	bool IsInsidePrimitive;	//Is the ray originating from inside the primitive? Used to calculate refraction.
	Primitive* HitObject;	//The object that the ray has hit
	float Distance;			//Distance to the hit object
	Vector3D HitPoint;		//The point where the ray intersected the object
	Vector3D Normal;		//The normal of the object at the intesection point
	
	Collision(bool isCollision): IsCollision(isCollision) {};	//Simple constructor

	//Detailed constructor
	Collision(bool isCollision, bool isInsidePrimitive, Primitive* hitObject, float distance, Vector3D normal, Vector3D hitPoint): 
				IsCollision(isCollision), IsInsidePrimitive(isInsidePrimitive), HitObject(hitObject), Distance(distance), Normal(normal), HitPoint(hitPoint)
				{};

	
    
};

#endif