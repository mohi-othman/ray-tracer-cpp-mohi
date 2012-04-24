//Class that defines the scene and renders it

#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Color.h"
#include "Camera.h"
#include "Light.h"
#include "Primitive.h"
#include "Shader.h"
#include "Sphere.h"

class Camera;

class Scene
{
public:
	int SizeX, SizeY;						//Size in pixels of the scene
	float PixelSize;						//The size of the pixel in real units
	Color AmbientLight;						//Ambient light of the scene
	Camera* SceneCamera;					//Camera used to render the scene
	std::vector <Primitive*> SceneObjects;	//List of all 3D objects in the scene
	std::vector <Light*> SceneLights;		//List of all light sources in the scene
	Shader* SceneShader;					//Shader used to shade the scene
	Color BackgroundColor;					//Background color of the scene

	//Constructor
	Scene() {};
	Scene(int sizeX, int sizeY, float pixelSize, Camera* sceneCamera, Color ambientLight, std::vector<Primitive*> sceneObjects, std::vector<Light*> sceneLights, Shader* sceneShader, Color backgroundColor):
		SizeX(sizeX), SizeY(sizeY), PixelSize(pixelSize), SceneCamera(sceneCamera), AmbientLight(ambientLight), SceneObjects(sceneObjects), SceneLights(sceneLights), SceneShader(sceneShader), BackgroundColor(backgroundColor){};
	~Scene()
	{
	}
	//Renders the scene to a view object.
	View Render();	

	//Main ray tracing function
	Point RayTrace(Ray ray, float refractionIndex, int level);	

	//Function to render reflection
	Color RenderReflection(Ray ray, Vector3D normal, Vector3D hitPoint, Primitive* hitObject, float refractionIndex, int level);

	//Function to render refraction
	Color RenderRefraction(Ray ray, Vector3D normal, Vector3D hitPoint, Primitive* hitObject, float refractionIndex, int level, bool IsInsidePrimitive);

	//Function to find intersection with a ray
	Collision Trace(Ray ray);
	
};

#endif