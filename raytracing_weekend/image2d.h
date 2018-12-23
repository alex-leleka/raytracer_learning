#pragma once

#include <memory>
#include "color_defines.h"

template <int N, int M>
struct Array2D
{
	using TDataType = Color;
	Array2D()
	{
		data = std::make_unique<TDataType[]>(N * M);
	}

	std::unique_ptr<TDataType[]> data;
	inline const TDataType& operator()(int i, int j) const { return data[i + j * N]; }
	inline TDataType& operator()(int i, int j) { return data[i + j * N]; }
	inline int GetRows() const { return N; }
	inline int GetColumns() const { return M; }
	inline int GetSize() const { return N * M; }

	inline int GetHeight() const { return N; }
	inline int GetWidth() const { return M; }
	inline const TDataType& Get(int column,int row) const { return data[row + column * N]; }
	inline const TDataType& GetByLinearIndex(int i) const { return data[i]; }

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