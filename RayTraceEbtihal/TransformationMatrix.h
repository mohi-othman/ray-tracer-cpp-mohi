#ifndef TRANSFORMATIONMATRIX_H
#define TRANSFORMATIONMATRIX_H

class TransformationMatrix
{
public:
	float mat[4][4];
	TransformationMatrix(void);
	TransformationMatrix GetCopy();
	void CopyFrom(TransformationMatrix m);
	TransformationMatrix GetInverse();
	TransformationMatrix GetTranspose();
	virtual TransformationMatrix ScaleMatrix(float scalingFactor);
	friend TransformationMatrix operator * (TransformationMatrix A, TransformationMatrix B);

};

#endif