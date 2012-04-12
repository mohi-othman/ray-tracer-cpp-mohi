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
	int SizeX, SizeY;
	float PixelSize;
	Color AmbientLight;
	Camera* SceneCamera;
	std::vector <Primitive*> SceneObjects;
	std::vector <Light*> SceneLights;
	Shader* SceneShader;
	Color BackgroundColor;

	Scene(int sizeX, int sizeY, float pixelSize, Camera* sceneCamera, Color ambientLight, std::vector<Primitive*> sceneObjects, std::vector<Light*> sceneLights, Shader* sceneShader, Color backgroundColor):
		SizeX(sizeX), SizeY(sizeY), PixelSize(pixelSize), SceneCamera(sceneCamera), AmbientLight(ambientLight), SceneObjects(sceneObjects), SceneLights(sceneLights), SceneShader(sceneShader), BackgroundColor(backgroundColor){};
	

	View Render();
	Point RayTrace(Ray ray, float refractionIndex, int level);
	Color RenderReflection(Ray ray, Vector3D normal, Vector3D hitPoint, Primitive* hitObject, float refractionIndex, int level);
	Color RenderRefraction(Ray ray, Vector3D normal, Vector3D hitPoint, Primitive* hitObject, float refractionIndex, int level, bool IsInsidePrimitive);
	Collision Trace(Ray ray);


};

#endif