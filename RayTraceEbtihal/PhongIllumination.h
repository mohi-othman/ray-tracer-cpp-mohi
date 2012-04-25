//Phong illumination shader

#ifndef PHONGILLUMINATION_H
#define PHONGILLUMINATION_H

#include "shader.h"
#include "SpecularShader.h"

class PhongIllumination :
    public Shader
{
public:
    Color GetColor(Primitive* HitObject, Light* LightSource, Vector3D ViewDirection, Vector3D LightDirection, Vector3D Normal);
};

#endif