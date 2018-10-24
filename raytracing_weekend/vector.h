#pragma once

#include <cmath>

template <typename T>
struct Vector3
{
	union
	{
		struct { T x, y, z; };
		struct { T r, g, b; };
		T data[3];
	};

	using VectorType = Vector3<T>;

	inline Vector3()
	{
	}

	inline Vector3(T x, T y, T z) 
		: x(x), y(y), z(z)
	{
	}

	inline T dot(const VectorType& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	inline VectorType cross(const VectorType& other) const
	{
		return VectorType{ y * other.z - z * other.y,
			-(x * other.z - z * other.x),
			x * other.y - y * other.x };
	}

	inline VectorType reciprocal() const
	{
		return VectorType{ 1.0f / x, 1.0f / y, 1.0f / z };
	}

	inline VectorType operator+(const VectorType& other) const
	{
		return VectorType{ x + other.x, y + other.y, z + other.z };
	}

	inline VectorType operator-(const VectorType& other) const
	{
		return VectorType{ x - other.x, y - other.y, z - other.z };
	}

	inline VectorType operator*(const VectorType& other) const
	{
		return VectorType{ x * other.x, y * other.y, z * other.z };
	}

	inline VectorType operator*(const T& number) const
	{
		return VectorType{ x * number, y * number, z * number };
	}

	inline VectorType operator/(const VectorType& other) const
	{
		return VectorType{ x / other.x, y / other.y, z / other.z };
	}

	inline VectorType operator/(const T& number) const
	{
		auto reciprocal = 1 / number;
		return VectorType{ x * reciprocal, y * reciprocal, z * reciprocal };
	}

	inline const VectorType& operator*=(const VectorType& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	inline const VectorType& operator*=(const T& scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	inline const VectorType& operator+=(const VectorType& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	inline const VectorType& operator-=(const VectorType& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	inline VectorType operator-() const
	{
		return VectorType{ -x , -y, -z };
	}

	inline T sqaredlength() const
	{
		return x * x + y * y + z * z;
	}

	inline T length() const
	{
		return sqrt(sqaredlength());
	}

	inline void makeunitvector() const
	{
		*this / length();
	}

	inline VectorType getunitvector() const
	{
		return *this / length();
	}

	inline T operator[] (int i) const
	{
		return data[i];
	}

	inline T& operator[] (int i)
	{
		return data[i];
	}
};

template <typename T>
inline Vector3<T> operator*(T number, const Vector3<T>& vector)
{
	return vector * number;
}

template <typename T>
inline T dot(const Vector3<T>& vectorA, const Vector3<T>& vectorB)
{
	return vectorA.dot(vectorB);
}

template <typename T>
inline Vector3<T> cross(const Vector3<T>& vectorA, const Vector3<T>& vectorB)
{
	return vectorA.cross(vectorB);
}

inline float lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}
template <typename T>
inline Vector3<T> lerp(const Vector3<T>& vectorA, const Vector3<T>& vectorB, const Vector3<T>& vectorT)
{
	Vector3<T> result{ lerp(vectorA.r, vectorB.r, vectorT.r), lerp(vectorA.g, vectorB.g, vectorT.g), lerp(vectorA.b, vectorB.b, vectorT.b) };
	return result;
}

template <typename T>
inline Vector3<T> lerp(const Vector3<T>& vectorA, const Vector3<T>& vectorB, T t)
{
	return lerp(vectorA, vectorB, Vector3<T>{t, t, t});
}

template <typename T>
inline Vector3<T> reflect(const Vector3<T>& vectorA, const Vector3<T>& vectorB)
{
	return vectorA - 2 * dot(vectorA, vectorB) * vectorB;
}

using Vector3F = Vector3<float>;