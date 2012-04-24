//Class for triangle primitive, dervied from the base Primitive class.

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "primitive.h"

class Triangle :
	public Primitive
{
private:
	Vector3D _u, _v, _normal;	//values generated when constructing triangle

public:
	Vector3D Point0;	//Vertices of the triangle
	Vector3D Point1;
	Vector3D Point2;

	Triangle(Vector3D point0, Vector3D point1, Vector3D point2);
	Collision Intersection(Ray ray);
	Vector3D GetNormal();	//retrieves normal
};

#endif
