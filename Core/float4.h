#pragma once


#ifndef FS_FLOAT4_H
#define FS_FLOAT4_H
// === HEADER BEGINS ===


#include <Core/_CommonTypes.h>
#include <xmmintrin.h>


namespace fs
{
	union UM128Data
	{
		__m128	m;
		struct { float x; float y; float z; float w; };
	};

	class Float4
	{
	public:
		explicit				Float4();
								Float4(float x, float y, float z, float w);
								Float4(const __m128& m);
								Float4(const Float4& b);
								Float4(Float4&& b) noexcept;
								~Float4();

	public:
		Float4&					operator=(const Float4& b);
		Float4&					operator=(Float4&& b) noexcept;

	public:
		Float4&					operator+=(const Float4& b);
		Float4&					operator-=(const Float4& b);

		// component-wise
		Float4&					operator*=(const Float4& b);
		// component-wise
		Float4&					operator/=(const Float4& b);

		// scalar
		Float4&					operator*=(float s);
		// scalar
		Float4&					operator/=(float s);

	public:
		Float4					operator+(const Float4& b) const;
		Float4					operator-(const Float4& b) const;

		// component-wise
		Float4					operator*(const Float4& b) const;
		// component-wise
		Float4					operator/(const Float4& b) const;

		// scalar
		Float4					operator*(float s) const;
		// scalar
		Float4					operator/(float s) const;

	public:
		Float4					operator==(const Float4& b) const noexcept;
		Float4					operator!=(const Float4& b) const noexcept;

	public:
		void					set(float x, float y, float z, float w);

		void					setX(float s) noexcept;
		void					setY(float s) noexcept;
		void					setZ(float s) noexcept;
		void					setW(float s) noexcept;

		float					getX() const noexcept;
		float					getY() const noexcept;
		float					getZ() const noexcept;
		float					getW() const noexcept;

	private:
		UM128Data				_data;


	// static functions
	public:
		static float				dot(const Float4& a, const Float4& b) noexcept
		{
			UM128Data result{ _mm_mul_ps(a._data.m, b._data.m) };
			return (result.x + result.y + result.z + result.w);
		}

		static Float4				cross(const Float4& a, const Float4& b) noexcept
		{
			UM128Data result
			{
				a._data.y * b._data.z - a._data.z * b._data.y,
				a._data.z * b._data.x - a._data.x * b._data.z,
				a._data.x * b._data.y - a._data.y * b._data.x,
				0,
			};
			return result.m;
		}

		static float				length(const Float4& a) noexcept
		{
			return sqrtf( Float4::dot(a, a) );
		}

		static Float4				normalize(const Float4& a) noexcept
		{
			float length{ Float4::length(a) };
			return (a / length);
		}
	};
	using float4				= Float4;
}


// === HEADER ENDS ===
#endif // !FS_FLOAT4_H
