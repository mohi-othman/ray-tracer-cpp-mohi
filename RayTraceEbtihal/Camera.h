#ifndef CAMERA_H
#define CAMERA_H

#include "View.h"
#include "Ray.h"
#include "Vector3D.h"

class Camera
{
public:
	virtual Ray GenerateRay(Vector3D target)=0;
	virtual View GetView(int width, int height, float PixelSize)=0;
};

#endif