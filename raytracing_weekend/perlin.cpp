#include "perlin.h"

#include "mathutils.h"
#include <algorithm>


Perlin::PerlinInternal Perlin::data;

Perlin::Perlin()
{
}


Perlin::~Perlin()
{
}

float Perlin::Noise(const Vector3F & p) const
{
	Vector3F scaledPoint = p * 4.0f;
	int i = int(scaledPoint.x) & 255;
	int j = int(scaledPoint.y) & 255;
	int k = int(scaledPoint.z) & 255;
	return data.GetNoiseValue(i, j, k);
}

float Perlin::PerlinInternal::GetNoiseValue(int i, int j, int k) const
{
	return randomFloat[permutationX[i] ^ permutationY[j] ^ permutationZ[k]];
}

void Perlin::PerlinInternal::GenerateRandomFloat()
{
	for (int i = 0; i < kSize; ++i)
	{
		randomFloat[i] = GetRandomFloat();
	}
}

void Perlin::PerlinInternal::GeneratePermutations(TPermutationType & arrayPermutations)
{
	for (int i = 0; i < kSize; ++i)
	{
		arrayPermutations[i] = i;
	}
	Permute(arrayPermutations);
}

void Perlin::PerlinInternal::Permute(TPermutationType & arrayPermutations)
{
	for (int i = kSize - 1; i > 0; --i)
	{
		int target = int(GetRandomFloat() * (i + 1));
		std::swap(arrayPermutations[i], arrayPermutations[target]);
	}
}

Perlin::PerlinInternal::PerlinInternal()
{
	GenerateRandomFloat();
	GeneratePermutations(permutationX);
	GeneratePermutations(permutationY);
	GeneratePermutations(permutationZ);
}
