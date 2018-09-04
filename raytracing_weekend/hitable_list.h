#pragma once

#include "hitable.h"

class HitableList : public Hitable
{
public:
	HitableList(Hitable** list, int size) : list(list), listSize(size) {}
	bool hit(const Ray& ray, float tMin, float tMax, HitRecord& recordOut) const override;
	Hitable** list{ nullptr };
	int listSize{ 0 };
};

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

HitableList* GetRandomScene();