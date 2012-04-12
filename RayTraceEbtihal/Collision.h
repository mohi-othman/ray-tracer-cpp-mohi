#ifndef COLLISION_H
#define COLLISION_H

#include "Primitive.h"
#include "Vector3D.h"
class Primitive;

class Collision
{
public:	
	bool IsCollision;
	bool IsInsidePrimitive;
	Primitive* HitObject;
	float Distance;
	Vector3D HitPoint;
	Vector3D Normal;
	
	Collision(bool isCollision): IsCollision(isCollision) {};
	Collision(bool isCollision, bool isInsidePrimitive, Primitive* hitObject, float distance, Vector3D normal, Vector3D hitPoint): 
				IsCollision(isCollision), IsInsidePrimitive(isInsidePrimitive), HitObject(hitObject), Distance(distance), Normal(normal), HitPoint(hitPoint)
				{};

	
    
};

#endif