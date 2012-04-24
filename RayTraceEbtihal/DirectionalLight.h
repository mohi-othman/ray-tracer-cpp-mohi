//Class for directional light, dervied from the base Light class

#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "light.h"
class DirectionalLight :
	public Light
{
public:
	Vector3D Direction;
	DirectionalLight(Vector3D direction, Color color, Vector3D attenuation);
	Vector3D GetLightDirection(Vector3D targetPoint);
};

#endif