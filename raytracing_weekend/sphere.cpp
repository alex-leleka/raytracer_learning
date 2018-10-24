#include "sphere.h"

Sphere::Sphere(const Vector3F& center, float radius, Material* material)
	: center(center)
	, radius(radius)
	, material(material)
{
}

bool Sphere::hit(const Ray& ray, float tMin, float tMax, HitRecord& recordOut) const
{
    Vector3F toRayOrigin = ray.origin() - center;
	float a = dot(ray.direction(), ray.direction());
	float b = dot(toRayOrigin, ray.direction());
	float c = dot(toRayOrigin, toRayOrigin) - radius * radius;
	float d = b * b - a * c;
	if (d >= 0)
	{
		float sqrtDiscriminant = sqrt(d);
		float len = (-b - sqrtDiscriminant) / a;
		if (len > tMin && len < tMax)
		{
			FillRecord(len, ray, recordOut);
			return true;
		}
		len = (-b + sqrtDiscriminant) / a;
		if (len > tMin && len < tMax)
		{
			FillRecord(len, ray, recordOut);
			return true;
		}

	}
	return false;
}

bool Sphere::boundingBox(float t0, float t1, Aabb & box) const
{
	Vector3F radiusCube = Vector3F{ radius, radius, radius };
	box = Aabb(center - radiusCube, center + radiusCube);
	return true;
}

void Sphere::FillRecord(float t, const Ray& ray, HitRecord& recordOut) const
{
	recordOut.t = t;
	recordOut.point = ray.point_at_parameter(t);
	recordOut.normal = (recordOut.point - center) / radius;
	recordOut.mat = material;
}