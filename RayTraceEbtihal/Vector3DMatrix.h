#ifndef VECTOR3DMATRIX_H
#define VECTOR3DMATRIX_H

#include "Vector3D.h"
#include "TransformationMatrix.h"

class Vector3DMatrix
{
public:
	float mat[4];
		
	void FromPoint(Vector3D p);
	void FromVector(Vector3D v);
	Vector3D ToVector3D();
	Vector3DMatrix Transform(TransformationMatrix vmatrix);
	Vector3DMatrix TransformNormal(TransformationMatrix vmatrix);	
};

#endif