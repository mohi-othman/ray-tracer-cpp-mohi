#include "PhongMaterial.h"


PhongMaterial::PhongMaterial(Color diffuseColor, Color specularColor, float exponent, Color transparentColor, Color reflectiveColor, float refractionIndex)
{
	PhongMaterial::DiffuseColor = diffuseColor;
	PhongMaterial::SpecularColor = specularColor;
	PhongMaterial::Exponent=exponent;
	PhongMaterial::TransparentColor=transparentColor;
	PhongMaterial::ReflectiveColor=reflectiveColor;
	PhongMaterial::RefractionIndex=refractionIndex;
	
	PhongMaterial::DiffuseCoeff = 1;
	PhongMaterial::ReflectionCoeff=0;		
}


