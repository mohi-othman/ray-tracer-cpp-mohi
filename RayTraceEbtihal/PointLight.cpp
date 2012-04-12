#include "PointLight.h"
#include "Color.h"

PointLight::PointLight(Vector3D location, Color color, Vector3D attenuation)
{
	PointLight::Location = location;
	PointLight::LightColor = color;
	PointLight::Attenuation = attenuation;
}

Vector3D PointLight::GetLightDirection(Vector3D targetPoint)
{
	Vector3D l = Location - targetPoint;
	l.Normalize();
	return l;
}



