#pragma once

#include "hitable.h"
#include "aabb.h"

class BhvNode :
	public Hitable
{
public:
	BhvNode(Hitable ** list, int n, float time0, float time1);
	BhvNode();
	virtual ~BhvNode();

	virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& recordOut) const override;
	virtual bool boundingBox(float t0, float t1, Aabb& box) const override;

	Aabb m_box;
	Hitable* m_left;
	Hitable* m_right;
};

