#include "BezierTranslationMatrix.h"


BezierTranslationMatrix::BezierTranslationMatrix(Vector3D controlPoint1, Vector3D controlPoint2, Vector3D endPoint)
{
	_deltaX = endPoint.x;
	_deltaY = endPoint.y;
	_deltaZ = endPoint.z;

	P1 = controlPoint1;
	P2 = controlPoint2;
	P3 = endPoint;

	mat[0][0] = 1;
	mat[1][1] = 1;
	mat[2][2] = 1;
	mat[3][3] = 1;
	mat[0][3] = _deltaX;
	mat[1][3] = _deltaY;
	mat[2][3] = _deltaZ;
}


TransformationMatrix BezierTranslationMatrix::ScaleMatrix(float scalingFactor)
{
	float t = scalingFactor;
	if (t > 1)
		t = 1;
	if (t < 0)
		t = 0;
	Vector3D P = 3 * pow(1 - t, 2) * t * P1
				+ 3 * (1 - t) * pow(t, 2) * P2
				+ pow(t, 3) * P3;

	_deltaX = P.x;
	_deltaY = P.y;
	_deltaZ = P.z;

	return TranslationMatrix(_deltaX, _deltaY, _deltaZ);
}
