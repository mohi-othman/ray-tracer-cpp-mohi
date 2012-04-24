// Class for perspective camera, dervied from the base Camera class

#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "camera.h"

class PerspectiveCamera :
	public Camera
{
public:
	Vector3D CameraLocation;
	Vector3D Direction; 
    Vector3D Up; 
    float Angle; 

	PerspectiveCamera(Vector3D cameraLocation, Vector3D direction, Vector3D up, float angle) : CameraLocation(cameraLocation), Direction(direction), Up(up), Angle(angle) {};
	Ray GenerateRay(Vector3D target);	
	View GetView(int width, int height, float pixelSize);
	
	Vector3D TranslatePoint(int x, int y, int width, int height, float pixelSize);	//Translate a pixel coordinate to real coordinates
	
};

#endif