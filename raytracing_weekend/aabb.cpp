#include "aabb.h"

Aabb surroundingBox(const Aabb& box0, const Aabb& box1)
{
	Vector3F small{
		ffmin(box0.GetMin().x, box1.GetMin().x),
		ffmin(box0.GetMin().y, box1.GetMin().y),
		ffmin(box0.GetMin().z, box1.GetMin().z)
	};
	Vector3F big{
		ffmin(box0.GetMax().x, box1.GetMax().x),
		ffmin(box0.GetMax().y, box1.GetMax().y),
		ffmin(box0.GetMax().z, box1.GetMax().z)
	};
	return Aabb(small, big);
}

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
