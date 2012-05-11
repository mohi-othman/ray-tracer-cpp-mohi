#include "TranslationMatrix.h"


TranslationMatrix::TranslationMatrix(float deltaX, float deltaY, float deltaZ)
{
	_deltaX = deltaX;
	_deltaY = deltaY;
	_deltaZ = deltaZ;

	mat[0][0] = 1;
	mat[1][1] = 1;
	mat[2][2] = 1;
	mat[3][3] = 1;
	mat[0][3] = deltaX;
	mat[1][3] = deltaY;
	mat[2][3] = deltaZ;
}

TransformationMatrix TranslationMatrix::ScaleMatrix(float scalingFactor)
{
	return TranslationMatrix(_deltaX * scalingFactor, _deltaY * scalingFactor, _deltaZ * scalingFactor);
}


