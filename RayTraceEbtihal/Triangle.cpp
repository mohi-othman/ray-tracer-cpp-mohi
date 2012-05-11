#include "Triangle.h"
#include "Globals.h"

Triangle::Triangle(Vector3D point0, Vector3D point1, Vector3D point2)
{
	Point0 = point0;
    Point1 = point1;
    Point2 = point2;

    // pre-calculate triangle edge vectors and plane normal            
    _u = Point1 - Point0;
    _v = Point2 - Point0;
    //_normal = (_u^_v);   
    _normal = (_v^_u);
	_normal.Normalize();
}

Collision Triangle::Intersection(Ray ray)
{
	//Formula taken from:
    //http://softsurfer.com/Archive/algorithm_0105/algorithm_0105.htm#intersect_RayTriangle()            
    Vector3D dir, w0, w;          // ray vectors
    float r, a, b;             // params to calc ray-plane intersect


    dir = ray.Direction;             // ray direction vector
    w0 = ray.Origin - Point0;
    a = -(_normal * w0);
    b = _normal * dir;
    if (fabs(b) < 0)
    {     // ray is parallel to triangle plane
        return Collision(false);
    }

    // get intersect point of ray with triangle plane
    r = a / b;
    if (r < 0.0)                        // ray goes away from triangle
        return Collision(false);    // => no intersect

    // for a segment, also test if (r > 1.0) => no intersect

    Vector3D hitPoint = ray.Origin + r * dir;           // intersect point of ray and plane

    // is I inside T?
    float uu, uv, vv, wu, wv, D;

    uu = (_u * _u);
    uv = (_u * _v);
    vv = (_v * _v);
    w = hitPoint - Point0;
    wu = (w * _u);
    wv = (w * _v);
    D = uv * uv - uu * vv;

    // get and test parametric coords
    float s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0.0 || s > 1.0)        // I is outside T
        return Collision(false);
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0)  // I is outside T
        return Collision(false);

    float dist = ray.Origin.Distance(hitPoint);

    return Collision(true, false, this, dist, _normal, hitPoint);                     // I is in T
}

Vector3D Triangle::GetNormal()
{
	return _normal;
}