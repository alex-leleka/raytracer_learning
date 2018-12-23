#include "texture.h"

#include <cmath>

// ConstantTexture
ConstantTexture::ConstantTexture(std::initializer_list<float> v)
{
	int index = 0;
	for (auto it = v.begin(); it != v.end(); ++it, ++index)
	{
		color[index] = *it;
	}
}

ConstantTexture::ConstantTexture(const Color & color)
	: color(color)
{
}

Color ConstantTexture::GetValue(float u, float v, const Vector3F & p) const
{
	return color;
}

// CheckerTexture
Color CheckerTexture::GetValue(float u, float v, const Vector3F & p) const
{
	Vector3F scaledCoord = 10.0f * p;
	float sines = std::sin(scaledCoord.x) * sin(scaledCoord.y) * sin(scaledCoord.z);

	return sines < 0.0f ? color0 : color1;
}
