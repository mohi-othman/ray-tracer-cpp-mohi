/* Ebtihal Kalantan
 * bitty_k18@hotmail.com
 * CS 484
 * March 2012
 *
 * $Id: raytrace.cpp 1961 2010-02-24 08:46:53Z mshafae $
 *
 */

#include <iostream>
#include <string>
#include "getopt.h"
#include "Parser.h"
#include "PNGBuilder.h"


///////////////////////////////
#include <fstream>
#include <vector>

#include "Scene.h"
#include "Vector3D.h"
#include "Color.h"
#include "PNGBuilder.h"

#include "Primitive.h"
#include "Sphere.h"
#include "Triangle.h"
#include "BoundingBox.h"
#include "Plane.h"
#include "TriangleMesh.h"

#include "Camera.h"
#include "OrthographicCamera.h"
#include "SimplePerspectiveCamera.h"
#include "PerspectiveCamera.h"

#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"

#include "Shader.h"
#include "PhongShader.h"
#include "PhongIllumination.h"

#include "Material.h"
#include "PhongMaterial.h"

#include "PlyModel.h"

#include "BezierTranslationMatrix.h"
#include "TransformationMatrix.h"
#include "TranslationMatrix.h"
#include "ScalingMatrix.h"
#include "RotationMatrix.h"
////////////////////////////////



using namespace std;

Parser *gTheScene;
string gProgramName;

void usage( string message = "" ){
	cerr << message << endl;
	cerr << gProgramName << " -i <inputfile> -o <outputfile> -d <depthfile>" << endl;
	cerr << "          -or-" << endl;
	cerr << gProgramName << " --input <inputfile> --output <outputfile> --depth <depthfile>" << endl;
	
}



void parseCommandLine( int argc, char **argv ){
	int ch;
	string inputFile( "" ), outputFile( "" ), depthFile( "" );
  int resolution;
	static struct option longopts[] = {
    { "input", required_argument, NULL, 'i' },
    { "output", required_argument, NULL, 'o' },
    { "depth", required_argument, NULL, 'd' },
    { "resolution", required_argument, NULL, 'r' },
    { "verbose", required_argument, NULL, 'v' },
    { "help", required_argument, NULL, 'h' },
    { NULL, 0, NULL, 0 }
	};

	
	while( (ch = getopt_long(argc, argv, "i:o:d:r:vh", longopts, NULL)) != -1 ){
		switch( ch ){
			case 'i':
				// input file
				inputFile = string(optarg);
				
				break;
			case 'o':
				// image output file
				outputFile = string(optarg);
				
				break;
			case 'd':
				// depth output file
				depthFile = string( optarg );
				
				break;
			case 'r':
        resolution = atoi(optarg);
        break;
      case 'v':
        // set your flag here.
        break;
      case 'h':
        usage( );
        break;
			default:
				// do nothing
				break;
		}
	}
	gTheScene = new Parser( inputFile, outputFile, depthFile );
}

int main( int argc, char **argv ){
	unsigned t0 = clock(), t1;
	
	Plane * plane = new Plane(10, Vector3D(0,1,0));
	plane->Material = new Material();
	plane->Material->DiffuseCoeff = 1;
	plane->Material->DiffuseColor= Color(.7,.7,0);
	plane->Material->Exponent = 64;
	plane->Material->SpecularCoeff = 0;	
	plane->Material->ReflectionCoeff=0;
	plane->Material->RefractionIndex=0;

	Sphere * sphere =new Sphere(Vector3D(-16, 0, 15), .75);
	sphere->Material = new Material();
	sphere->Material->DiffuseCoeff = .8;
	sphere->Material->DiffuseColor= Color(1,.2,.2);
	sphere->Material->Exponent = 64;
	sphere->Material->SpecularCoeff = .2;	
	sphere->Material->ReflectionCoeff=0;
	sphere->Material->RefractionIndex=0;

	FaceList * fl = readPlyModel("c:\\models\\icosahedron.ply");
	TriangleMesh * mesh = new TriangleMesh(*fl);	
	mesh->Material = new Material();
	mesh->Material->DiffuseCoeff = .2;
	mesh->Material->DiffuseColor= Color(.1,1,.9);
	mesh->Material->Exponent = 64;
	mesh->Material->SpecularCoeff = .8;	
	mesh->Material->ReflectionCoeff=0;
	mesh->Material->RefractionIndex=0;	
	
	BezierTranslationMatrix * tMatrix =new BezierTranslationMatrix( Vector3D(5, 15, -2),  Vector3D(15, -15, 1.7),  Vector3D(22, 0, -10));                        
	ScalingMatrix * sMatrix = new ScalingMatrix(3, 3, 3, sphere->Location);
	RotationMatrix * rMatrix = new RotationMatrix(9, Vector3D(0, 1, -.2), Vector3D(0, 0, -6));

	sphere->Transformations.push_back(tMatrix);
	sphere->Transformations.push_back(sMatrix);
	mesh->Transformations.push_back(rMatrix);

	vector<Primitive*> objs;
	objs.push_back(sphere);
	objs.push_back(mesh);
	objs.push_back(plane);

	SimplePerspectiveCamera * c = new SimplePerspectiveCamera(Vector3D(0, 0, -10),  Vector3D(0, 0, 1), Vector3D(0, 1, 0), 5);
	PointLight * l = new PointLight(Vector3D(0, 10, -2), Color(1, 1, 1), Vector3D(1, .5, .5));
	DirectionalLight * dl = new DirectionalLight( Vector3D(0, 0, 1), Color(.3,.3,.3), Vector3D(1, .5, .5));
	vector<Light*> ls;
	ls.push_back(l);
	ls.push_back(dl);
	
	Scene s = Scene(300,200,0.03, c, Color(.1,.1,.1), objs,ls,new PhongIllumination(),Color(0,0,0));
	PNGBuilder png;

	vector<View> result = s.Animate(4,20);
	std::vector<View>::iterator index = result.begin();
	std::vector<View>::iterator end = result.end();
	
	int i = 0;
	for(; index != end; index++)
	{			
		View v = (*index);
		char name [50];
		sprintf(name, "c:\\test\\cc%03d.png", i); 
		png.GeneratePNG(v, name);
		i++;
	}

	//s.TransformationScalingFactor = 1;
	//View v = s.Render();
	//png.GeneratePNG(v, "c:\\test\\cc1.png");
	/*string pathStr;
	gProgramName = argv[0];

	parseCommandLine( argc, argv );
	argc -= optind;
	argv += optind;
	if( gTheScene->hasInputSceneFilePath( ) &&
			gTheScene->hasOutputFilePath( ) &&
			gTheScene->hasDepthFilePath( ) ){
        
		gTheScene->parse( );	
        
		

			
	}else{
		usage( "You specify an input scene file, an output file and a depth file." );
	}
	*/
	t1 = clock() - t0;
	cout << "Execution time: " << t1 / CLOCKS_PER_SEC << " seconds\n";
	return( 0 );
}
