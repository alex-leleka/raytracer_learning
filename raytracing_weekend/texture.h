#pragma once

#include <initializer_list>
#include "color_defines.h"
#include "perlin.h"

class Texture
{
public:
	virtual Color GetValue(float u, float v, const Vector3F& p) const = 0;
};

class ConstantTexture : public Texture
{
public:
	ConstantTexture() {}
	ConstantTexture(std::initializer_list<float> v);
	ConstantTexture(const Color& color);
	Color GetValue(float u, float v, const Vector3F& p) const override;
private:
	Color color;
};

class CheckerTexture : public Texture
{
public:
	CheckerTexture() {}
	Color GetValue(float u, float v, const Vector3F& p) const override;
private:
	Color color0 { 0.1f, 0.1f, 0.1f };
	Color color1 { 0.9f, 0.9f, 0.9f };
};

class NoiseTexture : public Texture
{
public:
	NoiseTexture() {}
	Color GetValue(float u, float v, const Vector3F& p) const override;
private:
	Perlin perlin;
};