#include "SpecularShader.h"
#include <math.h>

//Specular lighting
Color SpecularShader::GetColor(Primitive* HitObject, Light* LightSource, Vector3D ViewDirection, Vector3D LightDirection, Vector3D Normal)
{
	Color result = Color();
    Vector3D L = LightDirection;
    Vector3D V = ViewDirection;
    Vector3D N = Normal;
	
    Vector3D R = L - 2 * (L * N) * N;
    float dot = V * R;

    if (dot > 0)
    {
        Color spec = pow(dot, HitObject->Material->Exponent) * HitObject->Material->SpecularCoeff * HitObject->Material->SpecularColor;
		result += spec * LightSource->LightColor;
    }
            
    return result;
}