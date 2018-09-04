#pragma once

#include "vector.h"

struct Ray
{
	Vector3F A; // origin
	Vector3F B; // direction

	const Vector3F& origin() const { return A; }
	const Vector3F& direction() const { return B; }
	Vector3F point_at_parameter(float t) const { return A + t * B; }
};