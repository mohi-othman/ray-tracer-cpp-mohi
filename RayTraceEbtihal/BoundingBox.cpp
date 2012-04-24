#include "BoundingBox.h"
#include "Globals.h"

//Formula from "Ray Tracing from the Ground Up"

Collision BoundingBox::Intersection(Ray ray)
{
	bool fRet = false;

    float ox = ray.Origin.x;
    float oy = ray.Origin.y;
    float oz = ray.Origin.z;
    float dx = ray.Direction.x;
    float dy = ray.Direction.y;
    float dz = ray.Direction.z;

    float tx_min, ty_min, tz_min;
    float tx_max, ty_max, tz_max;

    float a = 1.0 / dx;

    if (a >= 0)
    {
        tx_min = (_minVector.x - ox) * a;
        tx_max = (_maxVector.x - ox) * a;
    }
    else
    {
        tx_min = (_maxVector.x - ox) * a;
        tx_max = (_minVector.x - ox) * a;
    }

    float b = 1.0 / dy;
    if (b >= 0)
    {
        ty_min = (_minVector.y - oy) * b;
        ty_max = (_maxVector.y - oy) * b;
    }
    else
    {
        ty_min = (_maxVector.y - oy) * b;
        ty_max = (_minVector.y - oy) * b;
    }

    float c = 1.0 / dz;
    if (c >= 0)
    {
        tz_min = (_minVector.z - oz) * c;
        tz_max = (_maxVector.z - oz) * c;
    }
    else
    {
        tz_min = (_maxVector.z - oz) * c;
        tz_max = (_minVector.z - oz) * c;
    }

    float t0, t1;

    t0 = Max(tx_min, ty_min);
    t0 = Max(t0, tz_min);

    t1 = Min(tx_max, ty_max);
    t1 = Min(t1, tz_max);

    fRet = (t0 < t1 && t1 > EPSILON);

    if (fRet)
        return Collision(true);
    else
        return Collision(false);
}

