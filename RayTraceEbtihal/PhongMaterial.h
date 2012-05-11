//Class for Phong material, dervied from base Material class

#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H

#include "Material.h"

class PhongMaterial: public Material
{
public:
	//Basic constructor
	PhongMaterial(Color diffuseColor, Color specularColor, float exponent, Color transparentColor, Color reflectiveColor, float refractionIndex);	
};

#endif