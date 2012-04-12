#include "Scene.h"
#include "Globals.h"
#include "Sphere.h"

View Scene::Render(){
	View result = SceneCamera->GetView(SizeX, SizeY, PixelSize);
	
	Sphere x = Sphere(Vector3D(0,0,0),10);

    int level = 0;

    for (int x = 0; x < SizeX; x++)
    {
        for (int y = 0; y < SizeY; y++)
        {                   
			Vector3D targetPixel = result.GetPixel(x, y).realCoordinate;

            Ray ray = SceneCamera->GenerateRay(targetPixel);

            Point point = RayTrace(ray, 1, level);

            result.Pixels[(int)x, (int)y] = point;

        }
    }

    return result;
};
Point Scene::RayTrace(Ray ray, float refractionIndex, int level)
{
    Collision collision = Trace(ray);
	
    if (collision.IsCollision)
    {
        //Lighting
        Vector3D hitPoint = collision.HitPoint;
        Vector3D normal = collision.Normal;
        Color color = Color();

		std::vector<Light*>::iterator index = SceneLights.begin();
		std::vector<Light*>::iterator end = SceneLights.end();
        for(; index != end; index++)
        {			
			Light* light = (*index);
            Vector3D lightDir = light->GetLightDirection(hitPoint);
			lightDir.Normalize();

            Ray lightRay = Ray(hitPoint + lightDir * EPSILON, lightDir);

            //Check if object in shadows
            Collision shadowCollision = Trace(lightRay);

            if (!shadowCollision.IsCollision)
            {
				color += SceneShader->GetColor(collision.HitObject, light, ray.Direction, lightRay.Direction, normal);                        
            }
        }

        //Reflection
        if (collision.HitObject->Material->ReflectionCoeff > 0 && level <= MAX_DEPTH)
        {
            color += RenderReflection(ray, normal, hitPoint, collision.HitObject, refractionIndex, level);
        }

        //Refraction
        if (collision.HitObject->Material->ReflectionCoeff > 0 && level <= MAX_DEPTH)
        {
            color += RenderRefraction(ray, normal, hitPoint, collision.HitObject, refractionIndex, level, collision.IsInsidePrimitive);
        }

        color += AmbientLight;

        return Point(color, collision.Distance, Vector3D());
    }
    else
        return Point(BackgroundColor, INFINITY, Vector3D());
};

Color Scene::RenderReflection(Ray ray, Vector3D normal, Vector3D hitPoint, Primitive* hitObject, float refractionIndex, int level)
{
	Vector3D reflectionDirection = (ray.Direction - (2 * (ray.Direction * normal) * normal));
	reflectionDirection.Normalize();
    
	Ray reflectionRay = Ray(hitPoint + reflectionDirection * EPSILON, reflectionDirection);

    Point reflectionPoint = RayTrace(reflectionRay, refractionIndex, level + 1);

    return reflectionPoint.color * hitObject->Material->ReflectionCoeff * hitObject->Material->DiffuseColor;
};

Color Scene::RenderRefraction(Ray ray, Vector3D normal, Vector3D hitPoint, Primitive* hitObject, float refractionIndex, int level, bool IsInsidePrimitive)
{
	float refIndex = refractionIndex / hitObject->Material->RefractionIndex;
    Vector3D refNormal = normal * (IsInsidePrimitive ? -1 : 1);

    float cosI = -(refNormal * ray.Direction);
    float sinT2 = refIndex * refIndex * (1 - cosI * cosI);
    if (sinT2 <= 1)
    {
        float cosT = sqrtf(1 - sinT2);
        Vector3D refractionDirection = (refIndex * ray.Direction) + (refIndex * cosI - cosT) * refNormal;
        Ray refractionRay = Ray(hitPoint + refractionDirection * EPSILON, refractionDirection);
        Point refractionPoint = RayTrace(refractionRay, hitObject->Material->RefractionIndex, level + 1);

        Color absorbance = hitObject->Material->DiffuseColor * 0.15 * - refractionPoint.depth;
        Color transparency = Color(exp(absorbance.r), exp(absorbance.g), exp(absorbance.b));
        return refractionPoint.color * transparency;
    }
    return Color();
};

Collision Scene::Trace(Ray ray)
{
	float minT = INFINITY;
	Collision hit = Collision(false);

	std::vector<Primitive*>::iterator index = SceneObjects.begin();
	std::vector<Primitive*>::iterator end = SceneObjects.end();
    for(; index != end; index++)
    {			
		Primitive* obj = (*index);    
        Collision c = obj->Intersection(ray);
        if (c.IsCollision && c.Distance < minT)
        {
            minT = c.Distance;
            hit = c;
        }
    }

    return hit;
    
};
