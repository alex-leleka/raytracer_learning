#pragma once

#include "vector.h"
#include "ray.h"

inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }

class Aabb
{
public:
	Aabb(const Vector3F& a, const Vector3F& b);

	const Vector3F& GetMin() const { return minPoint; }
	const Vector3F& GetMax() const { return maxPoint; }

	inline bool hit(const Ray& r, float tmin, float tmax) const;

private:
	Vector3F minPoint;
	Vector3F maxPoint;
};

