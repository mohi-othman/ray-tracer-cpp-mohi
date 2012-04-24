#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>

#include <iostream>
#include "Entry.h"
#include "Vector3D.h"
#include "Globals.h"
#include "Sphere.h"
#include "PhongMaterial.h"
#include "PointLight.h"
#include "Primitive.h"
#include "OrthographicCamera.h"
#include "PhongShader.h"
#include "Scene.h"
#include "SimplePerspectiveCamera.h"
#include <vector>
#include <string>
#include "Plane.h"
#include "DirectionalLight.h"

using namespace std;
using namespace boost::gil;


Entry::Entry(void)
{
}

Entry::~Entry(void)
{
    
}

int main( int argc, char **argv ){
    #ifdef WIN32
        _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    #endif
	string pathStr;
	gProgramName = argv[0];
	boost::thread * drawing = NULL;

	parseCommandLine( argc, argv );
	argc -= optind;
	argv += optind;
	if( gTheScene->hasInputSceneFilePath( ) &&
			gTheScene->hasOutputFilePath( ) &&
			gTheScene->hasDepthFilePath( ) ){
        cout << "Parsing" << endl;
		gTheScene->parse( );

        if(gVerbose)
        {
		    cout << *gTheScene << endl;
        }	

        cout << "Tracing" << endl;
		if(gLiveView)
		{
			myTracer.setOpenGL(argc,argv);
		}
        myTracer.Trace(gTheScene,&drawing);

        cout << "Saving scene to files" << endl;
        gTheScene->drawScene();

		if(drawing != NULL)
		{
			drawing->join();
			delete drawing;
		}
	}else{
		usage( "You specify an input scene file, an output file and a depth file." );
	}
	if(gTheScene)
	{
		delete gTheScene;
	}

	return( 0 );
}
//int main(int argc, char *argv[]) 
//{	
//	Plane p = Plane(4.4, Vector3D(0, 1, 0));
//	Sphere s1 = Sphere(Vector3D(1, -0.8, 3), 2.5);
//	Sphere s2 = Sphere(Vector3D(-5.5f, -0.5, 7), 2);
//
//	PhongMaterial m1 = PhongMaterial(Color(.4,.3,.3), Color(1,1,1), 20, Color(0,0,0), Color(.2,.2,.2), 0);
//	PhongMaterial m2 = PhongMaterial(Color(.7,.7,.7), Color(1,1,1), 20, Color(0,0,0), Color(.2,.2,.2), 0);
//	PhongMaterial m3 = PhongMaterial(Color(.7,.7,1), Color(1,1,1), 20, Color(0,0,0), Color(.2,.2,.2), 0);
//	
//	m2.ReflectionCoeff = .6;
//	m2.DiffuseCoeff = .2;
//	m2.SpecularCoeff = .8;
//
//	m3.ReflectionCoeff= 1;
//	m3.DiffuseCoeff = .1;
//	m3.SpecularCoeff = .9;
//
//	p.Material = &m1;
//	s1.Material = &m2;
//	s2.Material = &m3;
//
//	PointLight l = PointLight(Vector3D(0, 5, 5), Color(.4,.4,.4), Vector3D(.5, .5, .5));
//	PointLight l2 = PointLight(Vector3D(2, 5, 1), Color(.6,.6,.8), Vector3D(.5, .5, .5));
//	DirectionalLight l3 = DirectionalLight(Vector3D(0, -1, 1), Color(1, .6, .8), Vector3D(.5, .5, .5));
//	
//	std::vector<Light*> lights;
//	std::vector<Primitive*> objects;
//
//	lights.push_back(&l);
//	lights.push_back(&l2);
//	lights.push_back(&l3);
//	
//	objects.push_back(&p);
//	objects.push_back(&s1);
//	objects.push_back(&s2);
//
//	//OrthographicCamera c = OrthographicCamera(Vector3D(0,0,-5), Vector3D(0,0,1), Vector3D(0,1,0));
//	SimplePerspectiveCamera c = SimplePerspectiveCamera(Vector3D(0,0,-5), Vector3D(0,0,1), Vector3D(0,1,0), 5);
//	PhongShader sh = PhongShader();
//	int width = 800;
//	int height = 600;
//	float pixelSize = 8.0/width;
//
//	Scene scene = Scene(width, height, pixelSize, &c, Color(0,0,0), objects, lights, &sh, Color(0,0,0));
//
//	View v = scene.Render();	
//	
//	rgb8_image_t img(width, height);       
//	
//	for(int x = 0; x<width; x++)
//	{
//		for(int y = 0; y<height; y++)
//		{			
//			Vector3D clr = v.GetPixel(x,y).color.ConvertToRGBValue();
//			rgb8_pixel_t p(clr.x, clr.y, clr.z);
//
//			view(img)(x,y) = p;
//		}
//	}
//
//	png_write_view("redsquare.png", const_view(img));
//
//	/*for(int x = 0; x<width; x++)
//	{
//		for(int y = 0; y<height; y++)
//		{
//			string ch;
//			Color clr = v.GetPixel(x,y).color;
//			float dd = (clr.b + clr.r + clr.g)/3;
//
//			if (dd>.75)
//				ch="@";
//			else if (dd>.50)
//				ch="*";
//			else if (dd>.001)
//				ch=".";	
//			else
//				ch=" ";
//			cout << ch;
//		}
//		cout << "\n";
//		
//		
//
//	}*/
//}
