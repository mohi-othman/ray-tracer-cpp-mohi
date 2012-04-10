// 3D vector class

#ifndef Vector3D_H
#define Vector3D_H

#include "math.h"

#define Length(A)       (sqrtf(A.x*A.x+A.y*A.y+A.z*A.z))                                    //Length of a vector
#define Normalize(A)    {float l=1/sqrtf(A.x*A.x+A.y*A.y+A.z*A.z);A.x*=l;A.y*=l;A.z*=l;}    //Normalize a vector
#define Cross(A,B)      {Vector3D( A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x );}

class Vector3D
{
public:
    struct { float x, y, z; };

	//Zeroed out vector constructor
    Vector3D() : x(0.0f), y(0.0f), z(0.0f) {}; 

    //Specific vector constructor
	Vector3D( float X, float Y, float Z ) : x( X ), y( Y ), z( Z ) {};	
	
    //Operator overloads
    friend Vector3D operator + ( const Vector3D& v1, const Vector3D& v2 )   { return Vector3D( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z ); }
    friend Vector3D operator + ( const Vector3D& v1, Vector3D* v2 )         { return Vector3D( v1.x + v2->x, v1.y + v2->y, v1.z + v2->z ); }
    void operator += ( Vector3D& V ) { x += V.x; y += V.y; z += V.z; }
	void operator += ( Vector3D* V ) { x += V->x; y += V->y; z += V->z; }

    friend Vector3D operator - ( const Vector3D& v1, const Vector3D& v2 )   { return Vector3D( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z ); }
	friend Vector3D operator - ( const Vector3D& v1, Vector3D* v2 )         { return Vector3D( v1.x - v2->x, v1.y - v2->y, v1.z - v2->z ); }
	void operator -= ( Vector3D& V ) { x -= V.x; y -= V.y; z -= V.z; }
	void operator -= ( Vector3D* V ) { x -= V->x; y -= V->y; z -= V->z; }
	Vector3D operator- () const { return Vector3D( -x, -y, -z ); }

    friend Vector3D operator * ( const Vector3D& v, float f ) { return Vector3D( v.x * f, v.y * f, v.z * f ); }	
	friend Vector3D operator * ( float f, const Vector3D& v ) { return Vector3D( v.x * f, v.y * f, v.z * f ); }
    void operator *= ( float f ) { x *= f; y *= f; z *= f; }

    //Dot product
    friend float operator * ( const Vector3D& v1, Vector3D& v2 ) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }	
	
};
#endif