#ifndef ROTATIONMATRIX_H
#define ROTATIONMATRIX_H

#include "transformationmatrix.h"
#include "TranslationMatrix.h"
#include "Vector3D.h"
#include <math.h>

class RotationMatrix :
	public TransformationMatrix
{
private:
	float _theta;
	Vector3D _rotationAxis;
	Vector3D _rotationPoint;

public:
	RotationMatrix(float theta, Vector3D rotationAxis, Vector3D rotationPoint);
	virtual TransformationMatrix ScaleMatrix(float scalingFactor);
};

#endif