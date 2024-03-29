//Base class for all camera types

#ifndef CAMERA_H
#define CAMERA_H

#include "View.h"
#include "Ray.h"
#include "Vector3D.h"

class Camera
{
public:
	// Function to generate a ray from the camera to the target pixel
	virtual Ray GenerateRay(Vector3D target)=0;

	// Function to generate a view based on the camera's settings
	virtual View GetView(int width, int height, float PixelSize)=0;
};

#endif