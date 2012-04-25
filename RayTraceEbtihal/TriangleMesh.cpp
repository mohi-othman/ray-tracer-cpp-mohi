#include "TriangleMesh.h"
#include "Triangle.h"
#include "BoundingBox.h"
#include "Globals.h"

TriangleMesh::TriangleMesh(FaceList faceList)
{
	std::vector<std::vector<int>>::iterator index = faceList.Faces.begin();
	std::vector<std::vector<int>>::iterator end = faceList.Faces.end();
    for(; index != end; index++)	
    {
		std::vector<int> face = (*index);
        Triangle triangle(faceList.Vertices[face[0]], faceList.Vertices[face[1]], faceList.Vertices[face[2]]);
		_triangles.push_back(triangle);
    }
    //find bounding box
    Vector3D minVector = faceList.Vertices[0];
    Vector3D maxVector = faceList.Vertices[0];

	for (int i = 1; i < faceList.Vertices.size(); i++)
    {
        minVector = Vector3D(Min(minVector.x, faceList.Vertices[i].x),
                             Min(minVector.y, faceList.Vertices[i].y),
                             Min(minVector.z, faceList.Vertices[i].z));
        maxVector = Vector3D(Max(maxVector.x, faceList.Vertices[i].x),
                             Max(maxVector.y, faceList.Vertices[i].y),
                             Max(maxVector.z, faceList.Vertices[i].z));
    }

    _boundingBox = BoundingBox(maxVector, minVector);
}

Collision TriangleMesh::Intersection(Ray ray)
{
	//try hit bounding box
    Collision bbCollision = _boundingBox.Intersection(ray);

    if (bbCollision.IsCollision)
    {
        float minT = INFINITY;
        Collision hit = Collision(false);

		std::vector<Triangle>::iterator index = _triangles.begin();
		std::vector<Triangle>::iterator end = _triangles.end();
		for(; index != end; index++)	        
        {
			Triangle t = (*index);
            Collision c = t.Intersection(ray);
            if (c.IsCollision)
            {
                if (c.Distance>0 && c.Distance < minT)
                {
                    hit = c;
                    minT = c.Distance;
                }
            }
        }

		if (hit.IsCollision)
        {            
            return Collision(true, false, this, hit.Distance, hit.Normal, hit.HitPoint); 
        }
        else
            return Collision(false);
    }
    return Collision(false);
}


