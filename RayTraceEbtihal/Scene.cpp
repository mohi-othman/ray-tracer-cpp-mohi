// Main ray tracing class.
// Based in part on code from:
// http://www.flipcode.com/archives/Raytracing_Topics_Techniques-Part_1_Introduction.shtml

#include "Scene.h"
#include "Globals.h"
#include "Sphere.h"

//Function to render the scene into a view
View Scene::Render(){
	//Construct empty view from camera
	View result = SceneCamera->GetView(SizeX, SizeY, PixelSize);
	
    int level = 0;
	int xy = 0;
    for (int y = 0; y < SizeY; y++)
    {
        for (int x = 0; x < SizeX; x++)
        {                   
			//get real coordinates of a pixel
			Vector3D targetPixel = result.GetPixel(x, y).realCoordinate;

			//construct ray from camera to pixel
            Ray ray = SceneCamera->GenerateRay(targetPixel);

			//ray trace that pixel
            Point point = RayTrace(ray, 1, level);

			//store results in view
            result.Pixels[xy] = point;

			xy++;
        }
    }

    return result;
};

//Main ray tracing function
Point Scene::RayTrace(Ray ray, float refractionIndex, int level)
{
	//trace the ray
    Collision collision = Trace(ray);
	
	//Check for collision
    if (collision.IsCollision)
    {   
        Vector3D hitPoint = collision.HitPoint;
        Vector3D normal = collision.Normal;
        Color color = Color();	//color of the pixel. Black for now

		//Iterate through all lights in the scene
		std::vector<Light*>::iterator index = SceneLights.begin();
		std::vector<Light*>::iterator end = SceneLights.end();
        for(; index != end; index++)
        {			
			Light* light = (*index);
            Vector3D lightDir = light->GetLightDirection(hitPoint);	//get direction from intersection to light source
			lightDir.Normalize();

			//construct ray from intersection to light source
            Ray lightRay = Ray(hitPoint + lightDir * EPSILON, lightDir);

            //Trace the light ray to check if object in shadows
            Collision shadowCollision = Trace(lightRay);

            if (!shadowCollision.IsCollision)
            {
				//Not in shadows. use the scene shader to calculate color contribution of the light
				color += SceneShader->GetColor(collision.HitObject, light, ray.Direction, lightRay.Direction, normal);                        
            }
        }

        //Check if the reflection coeffecient of the material allows for reflection
        if (collision.HitObject->Material->ReflectionCoeff > 0 && level <= MAX_DEPTH)
        {
			//Render the reflection
            color += RenderReflection(ray, normal, hitPoint, collision.HitObject, refractionIndex, level);
        }

        //Check if the refraction coeffecient of the material allows for refraction
		if (collision.HitObject->Material->RefractionIndex > 0 && level <= MAX_DEPTH)
        {
			//Render the refraction
            color += RenderRefraction(ray, normal, hitPoint, collision.HitObject, refractionIndex, level, collision.IsInsidePrimitive);
        }

		//Add ambient light color
        color += AmbientLight;

        return Point(color, collision.Distance, Vector3D());
    }
    else
		//No collision, return background color
        return Point(BackgroundColor, INFINITY, Vector3D());
};

//Function to render reflections
Color Scene::RenderReflection(Ray ray, Vector3D normal, Vector3D hitPoint, Primitive* hitObject, float refractionIndex, int level)
{
	Vector3D reflectionDirection = (ray.Direction - (2 * (ray.Direction * normal) * normal));	//calculate the direction of the reflection
	reflectionDirection.Normalize();
    
	Ray reflectionRay = Ray(hitPoint + reflectionDirection * EPSILON, reflectionDirection);		//construct reflection ray

    Point reflectionPoint = RayTrace(reflectionRay, refractionIndex, level + 1);				//trace the refletion ray

    return reflectionPoint.color * hitObject->Material->ReflectionCoeff * hitObject->Material->DiffuseColor;	//calculate reflection color
};

//Function to render refractions
Color Scene::RenderRefraction(Ray ray, Vector3D normal, Vector3D hitPoint, Primitive* hitObject, float refractionIndex, int level, bool IsInsidePrimitive)
{
	float refIndex = refractionIndex / hitObject->Material->RefractionIndex;	//calculate current refraction index
    Vector3D refNormal = normal * (IsInsidePrimitive ? -1 : 1);					//get the direction of the normal according to where we are in relation to 3D object

    float cosI = -(refNormal * ray.Direction);
    float sinT2 = refIndex * refIndex * (1 - cosI * cosI);
    if (sinT2 <= 1)
    {
        float cosT = sqrtf(1 - sinT2);
        Vector3D refractionDirection = (refIndex * ray.Direction) + (refIndex * cosI - cosT) * refNormal;
		refractionDirection.Normalize();
        Ray refractionRay = Ray(hitPoint + refractionDirection * EPSILON, refractionDirection);
        Point refractionPoint = RayTrace(refractionRay, hitObject->Material->RefractionIndex, level + 1);

        Color absorbance = hitObject->Material->DiffuseColor * 0.15 * - refractionPoint.depth;	//Calculate color of refraction
        Color transparency = Color(exp(absorbance.r), exp(absorbance.g), exp(absorbance.b));
        return refractionPoint.color * transparency;
    }
    return Color();
};

//Function to trace the ray and look for intersections
Collision Scene::Trace(Ray ray)	
{
	float minT = INFINITY;				//minimum distance
	Collision hit = Collision(false);	//reset collsion

	//iterate through all 3D objects in the scene
	std::vector<Primitive*>::iterator index = SceneObjects.begin();
	std::vector<Primitive*>::iterator end = SceneObjects.end();
    for(; index != end; index++)
    {			
		Primitive* obj = (*index);    

		//Check for intersection
        Collision c = obj->Intersection(ray);

		//Check if collision occured and if new distance is shorter than the current minimum distance
        if (c.IsCollision && c.Distance < minT)
        {
            minT = c.Distance;
            hit = c;
        }
    }

    return hit;    
};
