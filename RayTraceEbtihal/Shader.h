#ifndef SHADER_H
#define SHADER_H

#include "Color.h"
#include "Primitive.h"
#include "Light.h"
#include "Vector3D.h"

class Shader
{
public:
	virtual Color GetColor(Primitive* HitObject, Light* Light, Vector3D ViewDirection, Vector3D LightDirection, Vector3D Normal)=0;

};

#endif