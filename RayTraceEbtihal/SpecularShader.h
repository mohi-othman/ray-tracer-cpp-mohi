//Class for specular shading, dervied from the base Shader class

#ifndef SPECULARSHADER_H
#define SPECULARSHADER_H

#include "shader.h"
class SpecularShader :
	public Shader
{
public:
	Color GetColor(Primitive* HitObject, Light* LightSource, Vector3D ViewDirection, Vector3D LightDirection, Vector3D Normal);
};

#endif

