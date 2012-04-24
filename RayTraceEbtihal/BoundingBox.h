//Class for bounding box primitive, dervied from the base Primitive class.

#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "primitive.h"
class BoundingBox :
	public Primitive
{

private:
	Vector3D _maxVector;	//minimum coordinates of the bounding box
    Vector3D _minVector;	//maximum coordianted of the bounding box

public:
	BoundingBox() : _minVector(NULL_VECTOR), _maxVector(NULL_VECTOR) {};	//default consructor

	BoundingBox(Vector3D MaxVector, Vector3D MinVector)						//main constructor
	{
		_maxVector = MaxVector;
		_minVector = MinVector;
	}

	Collision Intersection(Ray ray);	
};

#endif