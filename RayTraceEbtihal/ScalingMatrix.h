#ifndef SCALINGMATRIX_H
#define SCALINGMATRIX_H

#include "transformationmatrix.h"
#include "Vector3D.h"

class ScalingMatrix :
	public TransformationMatrix
{
private: 
	float _deltaX, _deltaY, _deltaZ;
	Vector3D _refPoint;
public:
	ScalingMatrix(float deltaX, float deltaY, float deltaZ, Vector3D refPoint);
	virtual TransformationMatrix ScaleMatrix(float scalingFactor);
};

#endif