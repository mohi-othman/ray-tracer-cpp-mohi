#include "OrthographicCamera.h"

Ray OrthographicCamera::GenerateRay(Vector3D target)
{
	 return Ray(target, Direction);
}

View OrthographicCamera::GetView(int width, int height, float pixelSize)
{
	
	Vector3D p1 = TranslatePoint(0, 0, width, height, pixelSize);
    Vector3D p2 = TranslatePoint(width - 1, 0, width, height, pixelSize);
    Vector3D p3 = TranslatePoint(0, height - 1, width, height, pixelSize);
    Vector3D p4 = TranslatePoint(width - 1, height - 1, width, height, pixelSize);

    return View(width, height, p1, p2, p3, p4);
}

Vector3D OrthographicCamera::TranslatePoint(int x, int y, int width, int height, double pixelSize)
{		
   return CameraLocation +
                    (((Up ^ Direction) * (x + (-0.5 * width)) * pixelSize)) -
                    (Up * ((y + (-0.5 * height)) * pixelSize));
}

