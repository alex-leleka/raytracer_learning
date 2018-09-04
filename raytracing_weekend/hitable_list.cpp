#include "hitable_list.h"

#include "mathutils.h"
#include "material.h"
#include "sphere.h"

HitableList * GetRandomScene()
{
	const int Size = 501;
	Hitable **list = new Hitable*[Size];
	list[0] = new Sphere(Vector3F{ 0, -1000, 0 }, 1000, new Lambertian(Vector3F{ 0.5f, 0.5f, 0.5f }));
	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float chooseMaterial = GetRandomFloat();
			Vector3F center{ a + 0.9f * GetRandomFloat(), 0.2f, b + 0.9f * GetRandomFloat() };
			if ((center - Vector3F{ 4, 0.2f, 0 }).length() > 0.9f)
			{

			}
		}
	}
	list[i++] = new Sphere(Vector3F{ 0, 1, 0 }, 1, new Dielectric(1.5f));
	list[i++] = new Sphere(Vector3F{-4, 1, 0 }, 1, new Lambertian(Vector3F{ 0.4f, 0.2f, 0.1f }));
	list[i++] = new Sphere(Vector3F{ 4, 1, 0 }, 1, new Metal(Vector3F{ 0.7f, 0.6f, 0.5f }, 0.0f));
	HitableList* scene;

	return new HitableList{ list, i };
}