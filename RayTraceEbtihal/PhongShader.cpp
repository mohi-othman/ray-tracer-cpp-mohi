#include "PhongShader.h"
#include "DiffuseShader.h"
#include "SpecularShader.h"

//Combining diffuse shading and specular lighting
Color PhongShader::GetColor(Primitive* HitObject, Light* LightSource, Vector3D ViewDirection, Vector3D LightDirection, Vector3D Normal)
{
	Color result = Color();
    result += DiffuseShader().GetColor(HitObject, LightSource, ViewDirection, LightDirection, Normal);
    result += SpecularShader().GetColor(HitObject, LightSource, ViewDirection, LightDirection, Normal);            
    return result;
}