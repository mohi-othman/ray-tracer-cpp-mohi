#include "Primitive.h"
#include "Sphere.h"

Collision Sphere::Intersection(Ray ray)
{
	float A = ray.Direction * ray.Direction;
    float B = 2 * (ray.Origin - Location) * ray.Direction;
    float C = (ray.Origin - Location) * (ray.Origin - Location) - Radius * Radius;

    float d = B * B - 4 * A * C;
    if (d < 0)
        return Collision(false);

    float sqrtD = sqrtf(d);

    float q;
    if (B < 0)
        q = (-B - sqrtD) / 2;
    else
        q = (-B + sqrtD) / 2;

    float t0 = q / A;
    float t1 = C / q;

    if (t0 > t1)
    {
        float temp = t0;
        t1 = t0;
        t0 = temp;
    }

    if (t1 < 0)
        return Collision(false);

    if (t0 < 0)
    {
        //Origin inside sphere                
        Vector3D hitPoint1 = ray.Origin + ray.Direction * t1;
        return Collision(true, true, this, t1, GetNormal(hitPoint1), hitPoint1);
    }
	
    Vector3D hitPoint0 = ray.Origin + ray.Direction * t0;
    return Collision(true, false, this, t0, GetNormal(hitPoint0), hitPoint0);
}

Vector3D Sphere::GetNormal(Vector3D point)
{
	Vector3D n = point - Location;
    float temp = n * n;
    temp = 1 / sqrtf(temp);
    n = temp * n;

    return n;
}

