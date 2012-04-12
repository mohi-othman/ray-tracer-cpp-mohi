#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"
#include "Color.h"

class PointLight :
	public Light
{
public:
	PointLight(Vector3D location, Color color, Vector3D attenuation);
	Vector3D GetLightDirection(Vector3D targetPoint);
};

#endif