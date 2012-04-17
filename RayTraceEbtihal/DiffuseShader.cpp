#include "DiffuseShader.h"

//Diffuse Shading
Color DiffuseShader::GetColor(Primitive* HitObject, Light* LightSource, Vector3D ViewDirection, Vector3D LightDirection, Vector3D Normal)
{
	Vector3D L = LightDirection;
	L.Normalize();
    if (HitObject->Material->DiffuseCoeff > 0)
    {
        float dot = L * Normal;
        if (dot > 0)
        {
            float diff = dot * HitObject->Material->DiffuseCoeff;
			return diff * HitObject->Material->DiffuseColor * LightSource->LightColor;
        }
    }
            
    return Color();            
}
