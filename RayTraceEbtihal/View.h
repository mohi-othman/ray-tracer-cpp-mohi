#ifndef VIEW_H
#define VIEW_H

#include "Color.h"
#include "Vector3D.h"

class Point
{
public:
	struct {Color color; float depth; Vector3D realCoordinate;};
	Point(void){};		
	Point(Color myColor, float myDepth, Vector3D myCoord) : color(myColor),depth(myDepth),realCoordinate(myCoord){};
};

class View
{
public:
	Point* Pixels;
	int Width;
	int Height;
	View(int width, int height, Vector3D topLeftCorner, Vector3D topRightCorner, Vector3D bottomLeftCorner, Vector3D bottomRightCorner);
	~View(void);
	Point GetPixel(int x, int y);
};



#endif