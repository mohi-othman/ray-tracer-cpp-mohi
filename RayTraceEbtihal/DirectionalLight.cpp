#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector3D direction, Color color, Vector3D attenuation)
{
	DirectionalLight::Direction = direction;
	DirectionalLight::LightColor = color;
	DirectionalLight::Attenuation = attenuation;
}

Vector3D DirectionalLight::GetLightDirection(Vector3D targetPoint)
{
	//direction is reverse of the directional light direction
	return -1*Direction;
}

float DirectionalLight::GetDistance(Vector3D targetPoint)
{
	return INFINITY;
}
