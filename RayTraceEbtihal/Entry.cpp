#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL

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
#include <string>
#include <Magick++.h>

using namespace std;


Entry::Entry(void)
{
}

Entry::~Entry(void)
{
    
}

int main(int argc, char *argv[]) 
{
	Magick::InitializeMagick(*argv);

	Sphere s = Sphere(Vector3D(0,0,0), 3.2);
	PhongMaterial m = PhongMaterial(Color(1,1,1), Color(1,1,1), 20, Color(0,0,0), Color(.2,.2,.2), 0);
	s.Material = &m;

	PointLight l = PointLight(Vector3D(0,0,-5), Color(1,1,1), Vector3D(.2,.2,.2));
	
	std::vector<Light*> lights;
	std::vector<Primitive*> objects;

	lights.push_back(&l);
	objects.push_back(&s);

	OrthographicCamera c = OrthographicCamera(Vector3D(0,0,-5), Vector3D(0,0,1), Vector3D(0,1,0));
	DiffuseShader sh = DiffuseShader();
	int X = 80;
	int Y = 60;

	Scene scene = Scene(X, Y, .13, &c, Color(0,0,0), objects, lights, &sh, Color(0,0,0));

	View v = scene.Render();	

	for(int x = 0; x<X; x++)
	{
		for(int y = 0; y<Y; y++)
		{
			string ch;
			Color clr = v.GetPixel(x,y).color;
			float dd = (clr.b + clr.r + clr.g)/3;

			if (dd>.75)
				ch="@";
			else if (dd>.50)
				ch="*";
			else if (dd>.05)
				ch=".";
			else
				ch=" ";
			cout << ch;
		}
		cout << "\n";

	}
}
