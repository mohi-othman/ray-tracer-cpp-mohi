#include "ScalingMatrix.h"

ScalingMatrix::ScalingMatrix(float deltaX, float deltaY, float deltaZ, Vector3D refPoint)
{
	_deltaX = deltaX;
	_deltaY = deltaY;
	_deltaZ = deltaZ;

	_refPoint = refPoint;

	mat[0][0] = deltaX;
	mat[1][1] = deltaY;
	mat[2][2] = deltaZ;
	mat[3][3] = 1;
	mat[0][3] = (1 - deltaX) * refPoint.x;
	mat[1][3] = (1 - deltaY) * refPoint.y;
	mat[2][3] = (1 - deltaZ) * refPoint.z;
}


TransformationMatrix ScalingMatrix::ScaleMatrix(float scalingFactor)
{
	return ScalingMatrix((_deltaX - 1) * scalingFactor + 1, (_deltaY - 1) * scalingFactor + 1, (_deltaZ - 1) * scalingFactor + 1, _refPoint);
}