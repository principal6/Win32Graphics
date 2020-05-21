#pragma once


#ifndef FS_FLOAT4_H
#define FS_FLOAT4_H
// === HEADER BEGINS ===


#include <Core/_CommonTypes.h>
#include <xmmintrin.h>


namespace fs
{
	// SSE
	// private fields
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

		float					get(uint32 index) const noexcept;
		float					getX() const noexcept;
		float					getY() const noexcept;
		float					getZ() const noexcept;
		float					getW() const noexcept;

	private:
		__m128					_data;


	// static functions
	public:
		static float			dot(const Float4& a, const Float4& b) noexcept;
		static Float4			cross(const Float4& a, const Float4& b) noexcept;
		static float			length(const Float4& a) noexcept;
		static Float4			normalize(const Float4& a) noexcept;
	};

	// alias
	using float4				= Float4;
}


// === HEADER ENDS ===
#endif // !FS_FLOAT4_H
