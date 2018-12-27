#pragma once

#include "vector.h"


class Perlin
{
public:
	class PerlinInternal
	{
		static constexpr int kByteBitsSet = 255;
		static constexpr int kSize = kByteBitsSet + 1;
		using TPermutationType = int[kSize];
		void GeneratePermutations(TPermutationType& arrayPermutations);
		void Permute(TPermutationType& arrayPermutations);
		void GenerateRandomFloat();
	private:
		TPermutationType permutationX;
		TPermutationType permutationY;
		TPermutationType permutationZ;
		float randomFloat[kSize];
	public:
		PerlinInternal();
		float GetNoiseValue(int i, int j, int k) const;
	};

	Perlin();
	~Perlin();

	float Noise(const Vector3F& p) const;

	static PerlinInternal data;
};
