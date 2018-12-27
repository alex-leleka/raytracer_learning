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

Color NoiseTexture::GetValue(float u, float v, const Vector3F & p) const
{
	/*const Vector3F scaledCoord = 32.0f * p;
	int i = int(scaledCoord.x) & 255;
	int j = int(scaledCoord.y) & 255;
	int k = int(scaledCoord.z) & 255;
	float sum = (i ^ j ^ k & ~7) / (255.0f);
	const Vector3F colorHash{ sum, sum, sum };*/
	float sum = perlin.Noise(p);
	const Vector3F colorHash{ sum, sum, sum };
	return Color(colorHash);
}
