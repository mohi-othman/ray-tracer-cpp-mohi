#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
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

#include "TransformationMatrix.h"
#include "TranslationMatrix.h"
#include "BezierTranslationMatrix.h"
#include "RotationMatrix.h"
#include "ScalingMatrix.h"

#include "PlyModel.h"

using namespace std;

class Parser{
	public:
		Parser( string inputFilename = "", string outputFilename = "", string depthFilename = "", bool animate = false, float timeframe=0, int fps=0 );
		
		string& inputSceneFile( );
		string& outputFile( );
		string& depthFile( );
		
		Scene myScene;

		void setInputSceneFile( string file );
		void setOutputFile( string file );
		void setDepthFile( string file );

		bool hasInputSceneFilePath( );
		bool hasOutputFilePath( );
		bool hasDepthFilePath( );
        bool animated;
        float timeFrame;
        int FPS;
		bool parse( );

				
	private:				
		
		string myInputSceneFile;
		string myOutputFile;
		string myDepthFile;		
		int myNumberOfMaterials;
		vector<Primitive*> myGroup;
		vector<Material*> myMaterials;
		vector<Light*> myLights;
        
		// For parsing
		char currentLine[255];
		char currentToken[255];
		int lineNumber;
		int tokenCount;
		ifstream inputFileStream;
    int length;
    int i;
    int j;
		void nextToken( );
		void parseCamera( );
		void parseViewPlane( );
		void nextOnLine( );
		bool areMoreTokens( );
		void advance( );
		void checkToken( const char *str, const char *stage  );
		void parseBackground( );
		float parseFloat( );
		double parseDouble( );
		int parseInt( );
		string parseString( );
		void parseMaterials( );
		void parseGroup( );
        void parseTransformations( );
		void parseSphere(int materialIndex);
		void parsePlane(int materialIndex);
		void parseTriangle(int materialIndex);
		void parseModel(int materialIndex);
		void parseLights();
		void parsePointLight();
		void parseDirectionalLight();
        void parseTranslation(int objectIndex);
        void parseBezeirTranslation(int objectIndex);
        void parseRotation(int objectIndex);
        void parseScaling(int objectIndex);

		bool compareToken( const char *str );
};

std::ostream& operator <<( std::ostream &out, const Parser &s );


#endif