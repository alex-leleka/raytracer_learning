#include "hitable_list.h"

#include "mathutils.h"
#include "material.h"
#include "sphere.h"

HitableList * GetRandomScene()
{
	const int Size = 501;
	Hitable **list = new Hitable*[Size];
	list[0] = new Sphere(Vector3F{ 0, -1000, 0 }, 1000, new Lambertian(new NoiseTexture));
	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float chooseMaterial = GetRandomFloat();
			Vector3F center{ a + 0.9f * GetRandomFloat(), 0.2f, b + 0.9f * GetRandomFloat() };
			if ((center - Vector3F{ 4, 0.2f, 0 }).length() > 0.9f)
			{
				if (chooseMaterial < 0.8f)
				{
					list[i++] = new Sphere(center, 0.2f, 
						new Lambertian(new ConstantTexture{ GetRandomFloat()*GetRandomFloat(), GetRandomFloat()*GetRandomFloat(), GetRandomFloat()*GetRandomFloat() }));
				}
				else if (chooseMaterial < 0.95f)
				{
					list[i++] = new Sphere(center, 0.2f, 
						new Metal(0.5f * (Vector3F{ 1, 1, 1 } + Vector3F{ GetRandomFloat(), GetRandomFloat(), GetRandomFloat() }), 0.5f * GetRandomFloat()));
				}
				else
				{
					list[i++] = new Sphere(center, 0.2f, new Dielectric(1.5f));
				}
			}
			if (i == (Size-3))
			{
				break;
			}
		}
		if (i == (Size - 3))
		{
			break;
		}
	}
	list[i++] = new Sphere(Vector3F{ 0, 1, 0 }, 1, new Dielectric(1.5f));
	list[i++] = new Sphere(Vector3F{-4, 1, 0 }, 1, new Lambertian(new ConstantTexture{ 0.4f, 0.2f, 0.1f }));
	list[i++] = new Sphere(Vector3F{ 4, 1, 0 }, 1, new Metal(Vector3F{ 0.7f, 0.6f, 0.5f }, 0.0f));

	return new HitableList{ list, i };
}

bool HitableList::hit(const Ray& ray, float tMin, float tMax, HitRecord& recordOut) const
{
	HitRecord tempRecord;
	bool hitAnything = false;
	float closest = tMax;
	for (int i = 0; i < listSize; ++i)
	{
		if (list[i]->hit(ray, tMin, closest, tempRecord))
		{
			hitAnything = true;
			closest = tempRecord.t;
			recordOut = tempRecord;
		}
	}
	return hitAnything;
}

bool HitableList::boundingBox(float t0, float t1, Aabb & box) const
{
	if (listSize < 1)
	{
		return false;
	}
	Aabb tempBox;
	bool hitFirstElement = list[0]->boundingBox(t0, t1, tempBox);
	if (!hitFirstElement)
	{
		return false;
	}
	else
	{
		box = tempBox;
	}
	for (int i = 0; i < listSize; ++i)
	{
		if (list[i]->boundingBox(t0, t1, tempBox))
		{
			box = surroundingBox(box, tempBox);
		}
		else
		{
			return false;
		}
	}

	return true;
}
