// Base class for all light types.

#ifndef LIGHT_H
#define LIGHT_H

#include "Vector3D.h"
#include "Color.h"
class Light
{
public:
	Vector3D Location;		//Location of light
	Color LightColor;		//Color of the light
	Vector3D Attenuation;	//Attenuation values of the light

	//Gets the direction to the light source from the target point
	virtual Vector3D GetLightDirection(Vector3D targetPoint)=0;
};

#endif