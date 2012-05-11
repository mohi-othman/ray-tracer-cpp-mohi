#ifndef TRANSLATIONMATRIX_H
#define TRANSLATIONMATRIX_H

#include "TransformationMatrix.h"

class TranslationMatrix :
	public TransformationMatrix
{
private: 
	float _deltaX, _deltaY, _deltaZ;
public:
	TranslationMatrix(float deltaX, float deltaY, float deltaZ);	
	virtual TransformationMatrix ScaleMatrix(float scalingFactor);
};

#endif