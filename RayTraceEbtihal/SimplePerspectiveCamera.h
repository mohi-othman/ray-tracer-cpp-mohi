// Class for simple perspective camera, dervied from the base Camera class

#ifndef SIMPLE_PERSPECTIVE_CAMERA_H
#define SIMPLE_PERSPECTIVE_CAMERA_H

#include "Vector3D.h"
#include "camera.h"

class SimplePerspectiveCamera :
	public Camera
{
public:
	Vector3D CameraLocation;
    Vector3D Direction;
    Vector3D Up;
    float Distance;

	SimplePerspectiveCamera(Vector3D cameraLocation, Vector3D direction, Vector3D up, float distance) : CameraLocation(cameraLocation), Direction(direction), Up(up), Distance(distance) {};
	Ray SimplePerspectiveCamera::GenerateRay(Vector3D target);	
	View GetView(int width, int height, float pixelSize);
	
	Vector3D TranslatePoint(int x, int y, int width, int height, float pixelSize);	//Translate a pixel coordinate to real coordinates
};

#endif