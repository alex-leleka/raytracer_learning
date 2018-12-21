#pragma once

#include <memory>
#include "color_defines.h"

template <int N, int M>
struct Array2D
{
	Array2D()
	{
		data = std::make_unique<Color[]>(N * M);
	}

	std::unique_ptr<Color[]> data;
	inline const Color& operator()(int i, int j) const { return data[i + j * N]; }
	inline Color& operator()(int i, int j) { return data[i + j * N]; }
	inline int GetRows() const { return N; }
	inline int GetColumns() const { return M; }
	inline int GetSize() { return N * M; }

	inline int GetHeight() const { return N; }
	inline int GetWidth() const { return M; }
	inline const Color& Get(int column,int row) const { return data[row + column * N]; }
	static constexpr int SizeX = M;
	static constexpr int SizeY = N;
};

using ImageData = Array2D<400, 600>;


inline int ColorFloatToInt(float value, int maxVal)
{
	return int(value * maxVal + 0.5f);
}

inline ColorInt ColorFloatToInt(const Color& color, int maxVal)
{
	return ColorInt{ ColorFloatToInt(color.r,maxVal), ColorFloatToInt(color.g, maxVal), ColorFloatToInt(color.b, maxVal) };
}