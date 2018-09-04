#pragma once

#include "ray.h"
#include "mathutils.h"

class Camera
{
public:
	Camera(Vector3F lookFrom, Vector3F lookAt, Vector3F viewUp, float verticalFov, float aspect, float aperture, float focusDistance)
		: verticalFov(verticalFov)
		, aspect(aspect)
		, lensRadius(aperture *.5f)
	{
		Vector3F w = (lookFrom - lookAt).getunitvector();
		Vector3F u = cross(viewUp, w).getunitvector();
		Vector3F v = cross(w, u);
		float theta = verticalFov * 3.14159265358979323f / 180.0f;
		float halfHeight = tan(theta * .5f);
		float halfWidth = halfHeight * aspect;
		origin = lookFrom;
		lowerLeftCorner = origin - focusDistance * (halfWidth * u + halfHeight * v + w);
		horizontal = 2 * focusDistance * halfWidth * u;
		vertical = 2 * focusDistance * halfHeight * v;
	}

	Ray GetRay(float u, float v) const
	{
		Vector3F randomPointOnLens = lensRadius * GetRandomInUnitDisk();
		Ray r{ origin + randomPointOnLens, lowerLeftCorner + u * horizontal + v * vertical - origin - randomPointOnLens };
		return r;
	}

	float verticalFov{ 0 };
	float aspect{ 0 };
	float lensRadius{ 0 };
	Vector3F lowerLeftCorner{ -2.0f , -1.0f, -1.0f };
	Vector3F horizontal{ 4.0f, 0.0f, 0.0f };
	Vector3F vertical{ 0.0f, 2.0f, 0.0f };
	Vector3F origin{ 0.0f, 0.0f, 0.0f };
};