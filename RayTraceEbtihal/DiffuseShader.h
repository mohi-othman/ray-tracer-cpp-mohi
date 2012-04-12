#ifndef DIFFUSESHADER_H
#define DIFFUSESHADER_H

#include "shader.h"
#include "Primitive.h"
#include "Light.h"

class DiffuseShader :
	public Shader
{
public:
	Color GetColor(Primitive* HitObject, Light* LightSource, Vector3D ViewDirection, Vector3D LightDirection, Vector3D Normal);
};

#endif