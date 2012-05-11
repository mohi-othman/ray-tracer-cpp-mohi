#include "RotationMatrix.h"


RotationMatrix::RotationMatrix(float theta, Vector3D rotationAxis, Vector3D rotationPoint)
{
	_theta = theta;
	_rotationAxis = rotationAxis;
	_rotationAxis.Normalize();
	_rotationPoint = rotationPoint;

	float x, y, z, x2, y2, z2, c, s, t;
	x = _rotationAxis.x;
	y = _rotationAxis.y;
	z = _rotationAxis.z;
	x2 = pow(x, 2);
	y2 = pow(y, 2);
	z2 = pow(z, 2);
	c = cos(theta);
	s = sin(theta);
	t = 1 - c;

	TransformationMatrix R;
	R.mat[0][0] = t * x2 + c;
	R.mat[1][0] = t * x * y - s * z;
	R.mat[2][0] = t * x * z + s * y;

	R.mat[0][1] = t * x * y + s * z;
	R.mat[1][1] = t * y2 + c;
	R.mat[2][1] = t * y * z - s * x;

	R.mat[0][2] = t * x * z - s * y;
	R.mat[1][2] = t * y * z + s * x;
	R.mat[2][2] = t * z2 + c;

	R.mat[3][3] = 1;

	TranslationMatrix T = TranslationMatrix(rotationPoint.x, rotationPoint.y, rotationPoint.z);

	TransformationMatrix RT = R * T;

	CopyFrom(RT);
}


TransformationMatrix RotationMatrix::ScaleMatrix(float scalingFactor)
{
	return RotationMatrix(_theta * scalingFactor, _rotationAxis, _rotationPoint);
}
