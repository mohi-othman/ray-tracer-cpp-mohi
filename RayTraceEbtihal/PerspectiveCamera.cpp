#include "PerspectiveCamera.h"

Ray PerspectiveCamera::GenerateRay(Vector3D target)
{
	Vector3D direction = target - CameraLocation;
	direction.Normalize();
    return Ray(CameraLocation, direction);
}

//Construct view
View PerspectiveCamera::GetView(int width, int height, float pixelSize)
{
	
	Vector3D p1 = TranslatePoint(0, 0, width, height, pixelSize);
    Vector3D p2 = TranslatePoint(width - 1, 0, width, height, pixelSize);
    Vector3D p3 = TranslatePoint(0, height - 1, width, height, pixelSize);
    Vector3D p4 = TranslatePoint(width - 1, height - 1, width, height, pixelSize);

    return View(width, height, p1, p2, p3, p4);
}

Vector3D PerspectiveCamera::TranslatePoint(int x, int y, int width, int height, float pixelSize)
{	
	float Distance = width / (2 * tan(Angle)) * pixelSize;
    return (CameraLocation + (Direction * Distance)) +
                        (((Up^Direction) * (x + (-0.5 * width)) * pixelSize)) -
                    (Up * ((y + (-0.5 * height)) * pixelSize));

}