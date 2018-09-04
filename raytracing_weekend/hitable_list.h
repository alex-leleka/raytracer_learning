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

HitableList* GetRandomScene();