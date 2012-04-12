#ifndef LIGHT_H
#define LIGHT_H

#include "Vector3D.h"
#include "Color.h"
class Light
{
public:
	Vector3D Location;
	Color LightColor;
	Vector3D Attenuation;

	virtual Vector3D GetLightDirection(Vector3D targetPoint)=0;
};

#endif