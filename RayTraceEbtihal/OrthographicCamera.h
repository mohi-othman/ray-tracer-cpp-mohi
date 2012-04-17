// Class for orthographic camera, dervied from the base Camera class

#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H

#include "Vector3D.h"
#include "Camera.h"

class OrthographicCamera :
	public Camera
{
public:
	Vector3D CameraLocation;
    Vector3D Direction;
    Vector3D Up;
	
	OrthographicCamera(Vector3D location, Vector3D direction, Vector3D up) : CameraLocation(location), Direction(direction), Up(up) {};	
	Ray OrthographicCamera::GenerateRay(Vector3D target);	
	View GetView(int width, int height, float pixelSize);
	
	Vector3D TranslatePoint(int x, int y, int width, int height, float pixelSize);	//Translate a pixel coordinate to real coordinates
};


#endif