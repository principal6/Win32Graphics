#pragma once


#ifndef FS_FLOAT2_H
#define FS_FLOAT2_H
// === HEADER BEGINS ===


#include <Core/_CommonTypes.h>


namespace fs
{
	// non-SSE
	// public fields
	struct Float2
	{
		constexpr Float2()
		{
			__noop;
		}
		constexpr Float2(float x_, float y_) : x{ x_ }, y{ y_ }
		{
			__noop;
		}

		float x{};
		float y{};

		constexpr bool operator==(const Float2& b) const
		{
			return (x == b.x && y == b.y);
		}
		constexpr bool operator!=(const Float2& b) const
		{
			return !(*this == b);
		}

		constexpr Float2 operator+() const
		{
			return Float2(+x, +y);
		}
		constexpr Float2 operator-() const
		{
			return Float2(-x, -y);
		}

		constexpr Float2 operator+(const Float2& b) const
		{
			return Float2(x + b.x, y + b.y);
		}
		constexpr Float2 operator-(const Float2& b) const
		{
			return Float2(x - b.x, y - b.y);
		}
		constexpr Float2 operator*(const Float2& b) const
		{
			return Float2(x * b.x, y * b.y);
		}
	};
	using Position2 = Float2;
	using Size2 = Float2;
}


// === HEADER ENDS ===
#endif // !FS_FLOAT2_H
