#include "Vector3D.h"
#include "View.h"
#include "Globals.h"
#include <math.h>

View::View(int width, int height, Vector3D topLeftCorner, Vector3D topRightCorner, Vector3D bottomLeftCorner, Vector3D bottomRightCorner)
{
	Width = width;
	Height = height;
	Pixels = new Point[width * height];
	
	float distanceX = Length((topRightCorner-topLeftCorner));
    float distanceY = Length((bottomLeftCorner-topLeftCorner));
    float deltaX = distanceX / width;
    float deltaY = distanceY / height;
	 
    Vector3D vectorX = (topRightCorner - topLeftCorner);
    Vector3D vectorY = (bottomLeftCorner - topLeftCorner);

	vectorX.Normalize();
	vectorY.Normalize();

	for(int xy=0; xy < width*height; xy++)
	{		
		float x = xy % width;
		float y = floor((float)xy/width);

		Vector3D realCoordinate = Vector3D(topLeftCorner.x, topLeftCorner.y, topLeftCorner.z);
		realCoordinate += vectorX * (deltaX * x);
		realCoordinate += vectorY * (deltaY * y);
		Pixels[xy] = Point(Color(0,0,0), INFINITY, realCoordinate);
	}
	
}

Point View::GetPixel(int x, int y)
{
	return Pixels[y*Width + x];
}; 

