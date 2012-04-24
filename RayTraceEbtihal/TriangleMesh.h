//Class for triangle mesh primitive, dervied from the base Primitive class.

#ifndef TRIANGLE_MESH_H
#define TRIANGLE_MESH_H

#include <vector>
#include "primitive.h"
#include "BoundingBox.h"
#include "Triangle.h"

//struct to store data on faces
struct FaceList
{
	std::vector<Vector3D> Vertices;
    std::vector<std::vector<int>> Faces;
};

class TriangleMesh :
	public Primitive
{
private:
	BoundingBox _boundingBox;			//bounding box surrounding object
    std::vector<Triangle> _triangles;	//list of triangles in the object
public:
	FaceList Faces;						//list of faces and its data
	TriangleMesh(FaceList faceList);	//main constructor
	Collision Intersection(Ray ray);	
};



#endif