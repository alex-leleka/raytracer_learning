#pragma once

#include "vector.h"
#include "ray.h"
#include "aabb.h"
#include "config.h"

class Material;

struct HitRecord
{
	float t;
	Vector3F point;
	Vector3F normal;
	Material* mat;
	BHV_NODE_VISUAL_DEBUG_FIELD
};

class Hitable
{
public:
	virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& recordOut) const = 0;
	virtual bool boundingBox(float t0, float t1, Aabb& box) const = 0;
};