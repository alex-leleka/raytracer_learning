#include "mathutils.h"

#include <random>

Vector3F GetRandomInUnitSphere()
{
	Vector3F point;
	Vector3F one{ 1,1,1 };
	do
	{
		point = 2.0f*Vector3F{ GetRandomFloat(), GetRandomFloat(), GetRandomFloat() } - one;
	} while (point.length() >= 1.0f);
	return point;
}

Vector3F GetRandomInUnitDisk()
{
	Vector3F point;
	Vector3F one{ 1,1,0 };
	do
	{
		point = 2.0f*Vector3F{ GetRandomFloat(), GetRandomFloat(), 0 } - one;
	} while (point.length() >= 1.0f);
	return point;
}

float GetRandomFloat()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<float> dis(0.0f, 1.0f);
	return dis(gen);
}