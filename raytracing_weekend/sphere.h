#pragma once

#include "hitable.h"

class Sphere : public Hitable
{
public:
	Sphere(const Vector3F& center, float radius, Material* material);
	bool hit(const Ray& ray, float tMin, float tMax, HitRecord& recordOut) const override;
	Vector3F center;
	float radius;
	Material* material;
private:
	void FillRecord(float t, const Ray& ray, HitRecord& recordOut) const;
};