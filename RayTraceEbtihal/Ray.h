#ifndef RAY_H
#define RAY_H

#include "Vector3D.h"

class Ray
{
public:
	struct {Vector3D Origin, Direction}

	Ray(Vector 3D origin, Vector3D direction): Origin(origin), Direction(direction) {};
    
};

#endif