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
	string pathStr;
	gProgramName = argv[0];

	parseCommandLine( argc, argv );
	argc -= optind;
	argv += optind;
	if( gTheScene->hasInputSceneFilePath( ) &&
			gTheScene->hasOutputFilePath( ) &&
			gTheScene->hasDepthFilePath( ) ){
        unsigned t0 = clock(), t1;
		gTheScene->parse( );	
        t1 = clock() - t0;
		cout << "Execution time: " << t1 / CLOCKS_PER_SEC << " seconds\n";

			
	}else{
		usage( "You specify an input scene file, an output file and a depth file." );
	}


	return( 0 );
}
