#include "PhongIllumination.h"

//Phong Illumination
Color PhongIllumination::GetColor(Primitive* HitObject, Light* LightSource, Vector3D ViewDirection, Vector3D LightDirection, Vector3D Normal)
{
    Material * m = HitObject->Material;
    float a = LightSource->Attenuation.x;
    float b = LightSource->Attenuation.y;
    float c = LightSource->Attenuation.z;
    float d = Length(LightDirection);
    float att = 1 / (a + b * d + c * d * d);

    float reflectedLight = (Normal * LightDirection);
    if (reflectedLight < 0)
        return m->DiffuseColor;

    //get diffused color
    Color result = m->DiffuseColor * reflectedLight * LightSource->LightColor * att;

    //get specular
    result += SpecularShader().GetColor(HitObject, LightSource, ViewDirection, LightDirection, Normal);

    return result;
}
