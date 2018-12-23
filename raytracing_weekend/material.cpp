#include "material.h"

#include "ray.h"
#include "hitable.h"
#include "mathutils.h"

bool Lambertian::scatter(const Ray & rIn, const HitRecord & record, Vector3F & attenuation, Ray & scattered) const
{
	Vector3F target = record.normal + GetRandomInUnitSphere();
	scattered = Ray{ record.point, target };
	attenuation = albedo->GetValue(0, 0, record.point);
	return true;
}

bool Metal::scatter(const Ray & rIn, const HitRecord & record, Vector3F & attenuation, Ray & scattered) const
{
	Vector3F reflected = reflect(rIn.direction().getunitvector(), record.normal);
	scattered = Ray{ record.point, reflected + fuzz * GetRandomInUnitSphere() };
	attenuation = albedo;
	return dot(scattered.direction(), record.normal) > 0.0f;
}

bool refract(const Vector3F& v, const Vector3F& n, float ni_over_nt, Vector3F& refracted);
float schlick(float cosine, float refractionIndex);

bool Dielectric::scatter(const Ray & rIn, const HitRecord & record, Vector3F & attenuation, Ray & scattered) const
{
	Vector3F reflected = reflect(rIn.direction(), record.normal);
	attenuation = Vector3F{ 1, 1, 1 };
	float ni_over_nt;
	Vector3F outward_normal;
	float cosine;
	float dirDotNormal = dot(rIn.direction(), record.normal);
	if (dirDotNormal > 0)
	{
		outward_normal = -record.normal;
		ni_over_nt = refrationIndex;
		cosine = refrationIndex * dirDotNormal / rIn.direction().length();
	}
	else
	{
		outward_normal = record.normal;
		ni_over_nt = 1.0f / refrationIndex;
		cosine = - dirDotNormal / rIn.direction().length();
	}

	Vector3F refracted;
	float reflectedProbability;
	if (refract(rIn.direction(), outward_normal, ni_over_nt, refracted))
	{
		reflectedProbability = schlick(cosine, refrationIndex);
	}
	else
	{
		reflectedProbability = 1.0f;
	}

	if (GetRandomFloat() < reflectedProbability)
	{
		scattered = Ray{ record.point, reflected };
	}
	else
	{
		scattered = Ray{ record.point, refracted };
	}
	return true;
}

bool refract(const Vector3F& v, const Vector3F& n, float ni_over_nt, Vector3F& refracted)
{
	Vector3F vNormalized = v.getunitvector();
	float vdotn = dot(vNormalized, n);
	float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - vdotn * vdotn);
	if (discriminant > 0.0f)
	{
		refracted = ni_over_nt * (vNormalized - n * vdotn) - n * sqrt(discriminant);
		return true;
	}
	return false;
}

float schlick(float cosine, float refractionIndex)
{
	float r0 = (1.0f - refractionIndex) / (1.0f + refractionIndex);
	r0 = r0 * r0;
	return r0 + (1.0f - r0) * pow(1.0f - cosine, 5);
}
