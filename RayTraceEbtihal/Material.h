// Base material class for all material types.

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"

class Material
{
public:
	struct {
	float ReflectionCoeff;
	float DiffuseCoeff;
	float SpecularCoeff;
	float Exponent;
	float RefractionIndex;
	Color DiffuseColor;
	Color SpecularColor;
	Color TransparentColor;
	Color ReflectiveColor;
	};
};

#endif
