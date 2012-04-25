

#include "Parser.h"

Parser::Parser( string inputFilename, string outputFilename, string depthFilename ) :
	myInputSceneFile( inputFilename ),
	myOutputFile( outputFilename ),
	myDepthFile( depthFilename ),	
	lineNumber(0),
	tokenCount(0),
	length(0),
	i(0),
	j(0)
{
	myNumberOfMaterials = -1;	
	myScene.SceneShader = new PhongIllumination();// PhongShader();
	myScene.AmbientLight = Color();
}

bool Parser::parse( ){	
	bool ret = true;
	lineNumber = 0;
	tokenCount = 0;
	
	inputFileStream.open( myInputSceneFile.c_str( ), ios::in );
	if( inputFileStream.fail( ) ){
		cerr << "Error opening \"" << myInputSceneFile << "\" for reading." << endl;
		exit( 1 );
	}
	parseCamera( );
    parseViewPlane( );
    parseLights( );
	parseBackground( );
	parseMaterials( );
	parseGroup( );

	myScene.SceneLights = myLights;
	myScene.SceneObjects = myGroup;
				 
	inputFileStream.close();
	
	View v = myScene.Render();

	PNGBuilder png;

	png.GeneratePNG(v, myOutputFile.c_str());
	png.GenerateDepth(v, myDepthFile.c_str());
	return( ret );
}

bool Parser::hasInputSceneFilePath( void ){
	bool ret = true;
	if( myInputSceneFile == "" ){
		ret = false;
	}
	return( ret );
}

bool Parser::hasOutputFilePath( void ){
	bool ret = true;
	if( myOutputFile == "" ){
		ret = false;
	}
	return( ret );
}

bool Parser::hasDepthFilePath( void ){
	bool ret = true;
	if( myDepthFile == "" ){
		ret = false;
	}
	return( ret );
}


void Parser::setInputSceneFile( string file ){
	myInputSceneFile = file;
}

void Parser::setOutputFile( string file ){
	myOutputFile = file;
}

void Parser::setDepthFile( string file ){
	myDepthFile = file;
}

float Parser::parseFloat( ){
	float ret = (float)atof( currentToken );
	return( ret );
}

double Parser::parseDouble( ){
	double ret = (double)atof( currentToken );
	return( ret );
}

int Parser::parseInt( ){
	int ret = atoi( currentToken );
	return( ret );
}

string Parser::parseString( ){
    string ret = currentToken;
    return( ret );
}

bool Parser::compareToken( const char *str ){
    return (strcmp( currentToken, str) == 0);
}

void Parser::checkToken( const char *str, const char *stage  ){
	if( strcmp( currentToken, str ) != 0 ){
		cerr << stage << " parse error at line " << lineNumber << " token " << tokenCount << ": " << currentToken << endl;
		cerr << "Current line: " << currentLine << endl;
		cerr << "Expected \'" << str << "\'" << endl;
		exit( 1 );
	}
}

void Parser::parseCamera( ){
	float vec[3];
	nextToken( );
	bool fPerspective = false;
    bool fSimplePerspective = false;
    bool fOrthographic = false;
	Vector3D center, direction, up;
	float distance, angle;

	if(compareToken( "OrthographicCamera"))
    {
        fOrthographic = true;
    }
    else if(compareToken("SimplePerspectiveCamera"))
    {
        fSimplePerspective = true;
    }
	else if(compareToken("PerspectiveCamera"))
    {
        fPerspective = true;
    }
    else
    {
        checkToken("OrthographicCamera", "Camera");
    }
	nextToken( );
	checkToken( "{", "Camera" );
	nextToken( );
	checkToken( "center", "Camera" );
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		vec[i] = parseFloat( );
	}
    
	center = Vector3D(vec[0],vec[1],vec[2]);

	nextToken( );
	checkToken( "direction", "Camera" );
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		vec[i] = parseFloat( );
	}
    
	direction = Vector3D(vec[0],vec[1],vec[2]);
	direction.Normalize();

	nextToken( );
	checkToken( "up", "Camera" );
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		vec[i] = parseFloat( );
	}
    
	up = Vector3D(vec[0],vec[1],vec[2]);
	up.Normalize();

	nextToken( );
    
	if(fOrthographic)
	{
		myScene.SceneCamera =  new OrthographicCamera(center,direction,up);
	}
	else if(fSimplePerspective)
    {
        checkToken( "distance", "Camera");
        nextToken( );
        vec[0] = parseFloat( );
        distance = vec[0];
        nextToken( );
		myScene.SceneCamera = new SimplePerspectiveCamera(center,direction,up,distance);
    }
	else if (fPerspective)
	{
		checkToken( "angle", "Camera");
        nextToken( );
        vec[0] = parseFloat( );
        angle = vec[0];
        nextToken( );
		myScene.SceneCamera = &(PerspectiveCamera(center,direction,up,angle));
	}
	checkToken( "}", "Camera" );
}

void Parser::parseBackground( ){	
	float vec[3];
	
	nextToken( );
	checkToken( "Background", "Background" );
	nextToken( );
	checkToken( "{", "Camera" );
	
	nextToken( );
	checkToken( "color", "Background" );
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		vec[i] = parseFloat( );
	}
    	
	myScene.BackgroundColor = Color(vec[0],vec[1],vec[2]);
	nextToken( );
	checkToken( "}", "Background" );
}

void Parser::parseMaterials( ){
    nextToken( );
    checkToken( "Materials", "Materials" );
    nextToken( );
    checkToken( "{", "Materials" );
    nextToken();
    checkToken( "numMaterials", "Materials" );
    nextToken();
    myNumberOfMaterials = parseInt();
    for(int i = 0; i < myNumberOfMaterials; i++)
    {
        Color diffuseColor = Color(),specColor = Color(),transColor = Color(),reflColor = Color();		
		float exponent=0, refIndex=0;
        float vec[3];
        nextToken();
        checkToken( "PhongMaterial", "Materials" );
        nextToken();
        checkToken( "{", "Materials" );
        nextToken();
        checkToken( "diffuseColor", "Materials" );
        nextToken();
        for(int j = 0; j < 3; j++)
        {
            vec[j] = parseFloat();
            nextToken();
        }
        diffuseColor = Color(vec[0],vec[1],vec[2]);

        if(compareToken("specularColor"))
        {
            nextToken();
            for(int j = 0; j < 3; j++)
            {
                vec[j] = parseFloat();
                nextToken();
            }
            specColor = Color(vec[0],vec[1],vec[2]);
        }
        if(compareToken("exponent"))
        {
            nextToken();
            vec[0] = parseFloat();
            exponent=vec[0];
            nextToken();
        }
        if(compareToken("transparentColor"))
        {
            nextToken();
            for(int j = 0; j < 3; j++)
            {
                vec[j] = parseFloat();
                nextToken();
            }
            transColor = Color(vec[0],vec[1],vec[2]);
        }
        if(compareToken("reflexitiveColor"))
        {
            nextToken();
            for(int j = 0; j < 3; j++)
            {
                vec[j] = parseFloat();
                nextToken();
            }
            reflColor = Color(vec[0],vec[1],vec[2]);
        }
        if(compareToken("indexOfRefraction"))
        {
            nextToken();
            vec[0] = parseFloat();
            nextToken();
            refIndex = vec[0];
        }
		PhongMaterial * newMaterial = new PhongMaterial(diffuseColor, specColor, exponent,transColor,reflColor,refIndex);
        myMaterials.push_back(newMaterial);
        checkToken( "}", "Materials"); 
    }
    nextToken();
    checkToken( "}", "Materials"); 
}

void Parser::parseGroup( ){	
    int numObjects;
	int gCurrentMaterial;

    nextToken();
    checkToken( "Group", "Group");
    nextToken();
    checkToken( "{", "Group");
    nextToken();
    checkToken( "numObjects", "Group");
    nextToken();
    numObjects = parseInt();
    nextToken();
    for(int i = 0; i < numObjects; i++)
    {
        if(compareToken("MaterialIndex"))
        {
            checkToken("MaterialIndex", "Group");
            nextToken();
            gCurrentMaterial = parseInt();
            nextToken();
        }
        if(compareToken("Sphere"))
        {
            parseSphere(gCurrentMaterial );
        }
        else if(compareToken("Plane"))
        {
            parsePlane(gCurrentMaterial );
        }
        else if(compareToken("Triangle"))
        {
            parseTriangle(gCurrentMaterial );
        }
        else if(compareToken("TriangleMesh"))
        {
            parseModel(gCurrentMaterial );
        }
        else
        {
            checkToken("OBJECT3D","Group");
        }
        
        nextToken();
    }
    checkToken("}", "Group");
}

void Parser::parsePlane(int materialIndex )
{
    float vec[3];
    float distance;
	Vector3D normal;
    checkToken("Plane", "Plane");
    nextToken();
    checkToken( "{", "Plane");
    nextToken();
    checkToken("normal", "Plane");
    nextToken();
    for(int i = 0; i < 3; i++)
    {
        vec[i] = parseFloat();
        nextToken();
    }
	normal = Vector3D(vec[0],vec[1],vec[2]);
	normal.Normalize();
    checkToken("offset", "Plane");
    nextToken();
    distance = parseFloat();
    nextToken();
    checkToken("}", "Plane");

	Plane * p = new Plane(distance, normal);
	p->Material = myMaterials[materialIndex];
	myGroup.push_back(p);
}

void Parser::parseTriangle(int materialIndex )
{
    float vec[3][3];
	Vector3D p1,p2,p3;

    checkToken("Triangle", "Triangle");
    nextToken();
    checkToken("{", "Triangle");
    nextToken();
    checkToken("vertex0", "Triangle");
    nextToken();
    for(int i = 0; i < 3; i++)
    {
        vec[0][i] = parseFloat();
        nextToken();
    }	
	p1 = Vector3D(vec[0][0],vec[0][1],vec[0][2]);

    checkToken("vertex1", "Triangle");
    nextToken();
    for(int i = 0; i < 3; i++)
    {
        vec[1][i] = parseFloat();
        nextToken();
    }
	p2 = Vector3D(vec[1][0],vec[1][1],vec[1][2]);

    checkToken("vertex2", "Triangle");
    nextToken();
    for(int i = 0; i < 3; i++)
    {
        vec[2][i] = parseFloat();
        nextToken();
    }
	p3 = Vector3D(vec[2][0],vec[2][1],vec[2][2]);

    checkToken("}", "Triangle");
	
	Triangle *t = new Triangle(p1,p2,p3);
	t->Material = myMaterials[materialIndex];

	myGroup.push_back(t);
}

void Parser::parseSphere(int materialIndex ){
    float vec[3];
    float radius;
    checkToken("Sphere", "Sphere");
    nextToken();
    checkToken( "{", "Sphere");
    nextToken();
    checkToken( "center", "Sphere");
    nextToken();
    for(int j = 0; j < 3; j++)
    {
        vec[j] = parseFloat();
        nextToken();
    }
    checkToken( "radius", "Sphere");
    nextToken();
    radius = parseFloat();
    nextToken();
    checkToken( "}", "Sphere");

	Sphere * s = new Sphere(Vector3D(vec[0],vec[1],vec[2]), radius);
	s->Material = myMaterials[materialIndex];

    myGroup.push_back(s);
}

void Parser::parseModel(int materialIndex ){
    string var;
    FaceList * myFacelist;
    
    checkToken("TriangleMesh", "Mesh");
    nextToken();
    checkToken("{", "Mesh");
    nextToken();
    checkToken("ply_file", "Mesh");
    nextToken();
    var = parseString();
    nextToken();
    checkToken("}","Mesh");

    myFacelist = readPlyModel(var.c_str());
    
    TriangleMesh * myModel = new TriangleMesh(*myFacelist);	
    myModel->Material = myMaterials[materialIndex];

	myGroup.push_back(myModel);
    
    //delete myFacelist;
}

void Parser::parseViewPlane( ){
	// You will need to adjust this so that the result 
	// from parseFloat is stored somewhere meaningful.
    float var;
    nextToken();
    checkToken("ViewPlane", "ViewPlane");
    nextToken();
    checkToken( "{", "ViewPlane");
    nextToken();
    checkToken( "width", "ViewPlane");
    nextToken();
    var = parseFloat();
	myScene.SizeX = var;    
    nextToken();

    checkToken( "height", "ViewPlane");
    nextToken();
    var = parseFloat();
	myScene.SizeY = var;

    nextToken();
    checkToken( "pixelsize", "ViewPlane");
    nextToken();
    var = parseFloat();
	myScene.PixelSize = var;
    
    nextToken();
    checkToken("}", "ViewPlane");    
}

void Parser::parseLights( )
{
    int numLights;
    nextToken();
    checkToken("Lights","Lights");
    nextToken();
    checkToken("{","Lights");
    nextToken();
    checkToken("numLights", "Lights");
    nextToken();
    numLights = parseInt();

    for(int i = 0; i < numLights; i++)
    {
		nextToken();
		if (compareToken("PointLight"))
			parsePointLight();
		else 
			parseDirectionalLight();
    }
    nextToken();
    checkToken("}","Lights");
}
    
void Parser::parsePointLight()
{
    float pos[3];
    float col[3];
    float att[3];   
	Vector3D position;

    checkToken("PointLight", "Light");
    nextToken();
    checkToken("{", "Light");
    nextToken();
    checkToken("position","Light");
    for(int i = 0; i < 3; i++)
    {
        nextToken();
        pos[i] = parseFloat();
    }
	position = Vector3D(pos[0],pos[1],pos[2]);
	
    nextToken();
    checkToken("color","Light");
    for(int i = 0; i < 3; i++)
    {
        nextToken();
        col[i] = parseFloat();
    }
    nextToken();
    if( compareToken("attenuation"))
    {
        for(int i = 0; i < 3; i++)
        {
            nextToken();
            att[i] = parseFloat();
        }
        myLights.push_back(new PointLight(position ,Color(col[0],col[1],col[2]),Vector3D(att[0],att[1],att[2])));
        nextToken();
    }
    else
    {
        myLights.push_back(new PointLight(position ,Color(col[0],col[1],col[2]),Vector3D()));
    }
    checkToken("}","Light");
};

void Parser::parseDirectionalLight()
{
    float pos[3];
	float dir[3];
    float col[3];
    float att[3];
	Vector3D position, direction;

    checkToken("DirectionalLight", "Light");
    nextToken();
    checkToken("{", "Light");
    nextToken();
    checkToken("position","Light");
    for(int i = 0; i < 3; i++)
    {
        nextToken();
        pos[i] = parseFloat();
    }
	position = Vector3D(pos[0],pos[1],pos[2]);
	nextToken();

	checkToken("direction","Light");
    for(int i = 0; i < 3; i++)
    {
        nextToken();
        dir[i] = parseFloat();
    }
	direction = Vector3D(dir[0],dir[1],dir[2]);
	direction.Normalize();
    nextToken();

    checkToken("color","Light");
    for(int i = 0; i < 3; i++)
    {
        nextToken();
        col[i] = parseFloat();
    }
    nextToken();
    if( compareToken("attenuation"))
    {
        for(int i = 0; i < 3; i++)
        {
            nextToken();
            att[i] = parseFloat();
        }
        myLights.push_back(new DirectionalLight(direction,Color(col[0],col[1],col[2]),Vector3D(att[0],att[1],att[2])));
        nextToken();
    }
    else
    {
        myLights.push_back(new DirectionalLight(direction,Color(col[0],col[1],col[2]),Vector3D()));
    }
    checkToken("}","Light");
};

bool Parser::areMoreTokens( ){
	bool ret = false;
	if( j < length ){
		ret = true;
	}
	return( ret );
}

void Parser::advance( ){
	if( currentLine[j] == ' ' || currentLine[j] == '\t' || currentLine[j] == '\n' ){
		while( currentLine[j] == ' ' || currentLine[j] == '\t' || currentLine[j] == '\n' ){
			j++;
		}
		i = j;
	}
}

void Parser::nextOnLine( ){
	//advance( );
	while( currentLine[j] != ' ' && currentLine[j] != '\t' && currentLine[j] != '\n' && currentLine[j] != 0 ){
		j++;
	}
	//cout << "ending: " << i <<  ", " << j << endl;
	currentLine[j] = 0;
	int tmp = i;
	if( i != j ){
		while( i <= j ){
			currentToken[i - tmp] = currentLine[i];
			//cout << "copying: " << (i - tmp) <<  ", " << i << endl;
			i++;
		}
		//cerr << lineNumber << ": " << ++tokenCount << ": '" << currentToken << "'" << endl;
	}
	j++;
	i = j;
}

void Parser::nextToken( ){
	if( !inputFileStream.eof( ) ){
		advance( );
		if( areMoreTokens( ) ){
			nextOnLine( );
		}else{
			do{
				inputFileStream.getline( currentLine, sizeof(currentLine) );
				lineNumber++;
				length = strlen( currentLine );
				//cerr << "new line of length: " << length << endl;
			}while( length <= 0 );
			i = 0;
			j = 0;
			advance( );
			//cerr << "Line: " << currentLine << endl;
			if( areMoreTokens( ) ){
				nextOnLine( );
			}
		}
	}
}





