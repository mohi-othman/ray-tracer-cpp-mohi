#ifndef PhongMaterial_H

#include "Material.h"

class PhongMaterial: public Material
{
public:
	PhongMaterial(Color diffuseColor, Color specularColor, float exponent, Color transparentColor, Color reflectiveColor, float refractionIndex);	
};

#endif