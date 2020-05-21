#pragma once


#ifndef FS_FLOAT4X4_H
#define FS_FLOAT4X4_H
// === HEADER BEGINS ===


#include <Core/Float4.h>


namespace fs
{
	// right-handed 4x4 matrix
	class Float4x4
	{
	public:
		explicit				Float4x4();
								Float4x4(float m00, float m01, float m02, float m03,
										float m10, float m11, float m12, float m13,
										float m20, float m21, float m22, float m23,
										float m30, float m31, float m32, float m33);
								Float4x4(const Float4& row0, const Float4& row1, const Float4& row2, const Float4& row3);
								Float4x4(const Float4x4& b);
								Float4x4(Float4x4&& b) noexcept;
								~Float4x4();

	public:
		Float4x4&				operator=(const Float4x4& b);
		Float4x4&				operator=(Float4x4&& b) noexcept;

	public:
		Float4x4				operator+(const Float4x4& b) const;
		Float4x4				operator-(const Float4x4& b) const;

		// scalar
		Float4x4				operator*(float s) const;
		// scalar
		Float4x4				operator/(float s) const;

		// matrix(l) * matrix(r)
		Float4x4				operator*(const Float4x4& r) const;
		// matrix * vector
		Float4					operator*(const Float4& v) const;

	public:
		void					set(float m00, float m01, float m02, float m03,
									float m10, float m11, float m12, float m13,
									float m20, float m21, float m22, float m23,
									float m30, float m31, float m32, float m33);
		void					set(const Float4& row0, const Float4& row1, const Float4& row2, const Float4& row3);
		void					setZero();
		void					setIdentity();

	public:
		Float4					mul(const Float4& v) const noexcept;
		Float4x4				mul(const Float4x4& m) const noexcept;

	private:
		Float4					_row[4];


	// static functions
	public:
		static Float4			mul(const Float4x4& m, const Float4& v) noexcept;
		static Float4x4			mul(const Float4x4& l, const Float4x4& r) noexcept;
	};

	// alias
	using float4x4 = Float4x4;
}


// === HEADER ENDS ===
#endif // !FS_FLOAT4X4_H
