#pragma once

#include "vector.h"
#include "texture.h"

struct Ray;
struct HitRecord;

class Material
{
public:
	virtual bool scatter(const Ray& rIn, const HitRecord& record, Vector3F& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material
{
public:
	Lambertian(const Texture* albedo) : albedo(albedo) {}
	bool scatter(const Ray& rIn, const HitRecord& record, Vector3F& attenuation, Ray& scattered) const override;
	const Texture* albedo;
};

class Metal : public Material
{
public:
	Metal(const Vector3F& albedo, float fuzz) : albedo(albedo), fuzz(fuzz) {}
	bool scatter(const Ray& rIn, const HitRecord& record, Vector3F& attenuation, Ray& scattered) const override;
	Vector3F albedo{ 0, 0, 0 };
	float fuzz{ 1.0f };
};

class Dielectric : public Material
{
public:
	Dielectric(float refrationIndex) : refrationIndex(refrationIndex) {}
	bool scatter(const Ray& rIn, const HitRecord& record, Vector3F& attenuation, Ray& scattered) const override;
	float refrationIndex{ 1.0f };
};