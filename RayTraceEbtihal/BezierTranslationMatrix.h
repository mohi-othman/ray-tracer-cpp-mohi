#ifndef BEZIERTRANSLATIONMATRIX_H
#define BEZIERTRANSLATIONMATRIX_H

#include "transformationmatrix.h"
#include "TranslationMatrix.h"
#include "Vector3D.h"
#include <math.h>

class BezierTranslationMatrix :
	public TransformationMatrix
{
private: 
	float _deltaX, _deltaY, _deltaZ;
	Vector3D P1, P2, P3;
public:
	BezierTranslationMatrix(Vector3D controlPoint1, Vector3D controlPoint2, Vector3D endPoint);
	virtual TransformationMatrix ScaleMatrix(float scalingFactor);
};

#endif