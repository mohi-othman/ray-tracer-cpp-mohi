//Class used to store data on the view that results from a scene rendering

#ifndef VIEW_H
#define VIEW_H

#include "Color.h"
#include "Vector3D.h"

class Point	//Class used to store data on a single point in the view
{
public:
	struct {
		Color color;				//Color of the point
		float depth;				//Distance from camera
		Vector3D realCoordinate;	//Real coordinates of the point
	};
	Point(void){};		//default constructor

	//Main constructor
	Point(Color myColor, float myDepth, Vector3D myCoord) : color(myColor),depth(myDepth),realCoordinate(myCoord){};
};


// View class
class View
{
public:
	Point* Pixels;	//Array to store data on all pixels
	int Width;		//Width of the view in pixels
	int Height;		//Height of the view in pixels
	View(int width, int height, Vector3D topLeftCorner, Vector3D topRightCorner, Vector3D bottomLeftCorner, Vector3D bottomRightCorner); //Main constructor
	
	Point GetPixel(int x, int y);	//Retrieves a pixel at a given coordinate
};



#endif