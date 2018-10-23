#include "aabb.h"



Aabb::Aabb(const Vector3F& a, const Vector3F& b)
	: minPoint(a)
	, maxPoint(b)
{
}

bool Aabb::hit(const Ray & r, float tmin, float tmax) const
{
	auto directionReciprocal { r.direction().reciprocal() };
	auto intervalMin { (minPoint - r.origin()) * directionReciprocal };
	auto intervalMax{ (maxPoint - r.origin()) * directionReciprocal };

	for (int i = 0; i < 3; ++i)
	{
		float t0 = ffmin(intervalMin[i], intervalMax[i]);
		float t1 = ffmax(intervalMin[i], intervalMax[i]);
		tmin = ffmin(t0, tmin);
		tmax = ffmax(t1, tmax);
		if (tmax <= tmin)
		{
			return false;
		}
	}
	return true;
}
