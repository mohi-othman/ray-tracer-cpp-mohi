#ifndef COLLISION_H
#define COLLISION_H

#include "Vector3D.h"
#include "Primitive.h"

class Collision
{
public:
	struct
	{
		bool IsCollision;
		bool IsInsidePrimitive;
		Primitive* HitObject;
		float Distance;
		Vector3D HitPoint;
		Vector3D Normal;
	}
	Collision(bool isCollision): IsCollision(isCollision) {};
	Collision(bool isCollisionbool, bool isInsidePrimitive, Primitive* hitObject, float distance, Vector3D distance, Vector3D normal): 
				IsCollision(isCollision), IsInsidePrimitive(isInsidePrimitive), HitObject(hitObject),  Distance(distance), Distance(distance), Normal(normal) {};
    
};

#endif