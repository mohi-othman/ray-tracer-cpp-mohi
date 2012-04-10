#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Material.h"
#include "Vector3D.h"
#include "Ray.h"
#include "Collision.h"

class Primitive
{
public:
    Primitive(void);
    ~Primitive(void);
    
    Material GetMaterial();
    void SetMaterial(Material m);

    Vector3D GetLocation();
    void SetLocation(Vector3D l);

    Collision Intersection(Ray ray);
private:
    Material _material;
    Vector3D _location;
};
#endif;