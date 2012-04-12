#include <iostream>
#include "Entry.h"
#include "Vector3D.h"
#include "Globals.h"
#include "Sphere.h"
#include "PhongMaterial.h"
#include "PointLight.h"
#include "Primitive.h"
#include "OrthographicCamera.h"
#include "DiffuseShader.h"
#include "Scene.h"
#include <vector>

using namespace std;


Entry::Entry(void)
{
}

Entry::~Entry(void)
{
    
}

int main(int argc, char *argv[]) 
{
	Sphere s = Sphere(Vector3D(.5,0,3), 2.2);
	PhongMaterial m = PhongMaterial(Color(.2,.5,.7), Color(1,1,1), 20, Color(0,0,0), Color(.2,.2,.2), 0);
	s.Material = &m;

	PointLight l = PointLight(Vector3D(1,1,-2), Color(1,1,1), Vector3D(.2,.2,.2));
	
	std::vector<Light*> lights;
	std::vector<Primitive*> objects;

	lights.push_back(&l);
	objects.push_back(&s);

	OrthographicCamera c = OrthographicCamera(Vector3D(0,0,-5), Vector3D(0,0,1), Vector3D(0,1,0));
	DiffuseShader sh = DiffuseShader();
	Scene scene = Scene(80, 60, .1, &c, Color(0,0,0), objects, lights, &sh, Color(0,0,0));
}
