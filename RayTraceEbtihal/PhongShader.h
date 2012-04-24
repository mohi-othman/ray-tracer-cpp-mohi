//Class for Phong shading, dervied from Shader class. Combines DiffuseShader and SpecularShader into one shader.
#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include "shader.h"

class PhongShader :
	public Shader
{
public:
	Color GetColor(Primitive* HitObject, Light* LightSource, Vector3D ViewDirection, Vector3D LightDirection, Vector3D Normal);
};

#endif