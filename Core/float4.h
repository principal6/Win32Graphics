#pragma once


#ifndef FS_FLOAT4_H
#define FS_FLOAT4_H
// === HEADER BEGINS ===


#include <Core/_CommonTypes.h>
#include <xmmintrin.h>


namespace fs
{
	class Float4;
	class Quaternion;

	// SSE
	// private fields
	class Float4 final
	{
	public:
		explicit				Float4();
		explicit				Float4(float x, float y, float z, float w);
		explicit				Float4(const __m128& m);
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

	public:
		Quaternion				asQuaternion() const noexcept;

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


	// q == a + bi + cj + dk
	class Quaternion final
	{
	public:
		explicit				Quaternion();
		explicit				Quaternion(float a, float b, float c, float d);
		explicit				Quaternion(const Float4& v);
								Quaternion(const Quaternion& q);
								~Quaternion();

	public:
		// Hamilton product
		Quaternion				operator*(const Quaternion& q) const noexcept;

	public:
		Float4					asFloat4() const noexcept;

		Quaternion				reciprocal() const noexcept;

	private:
		float					getA() const noexcept;
		float					getB() const noexcept;
		float					getC() const noexcept;
		float					getD() const noexcept;

	// static functions
	private:
		// q*
		static Quaternion		conjugate(const Quaternion& q) noexcept;

		// ||q||
		static float			norm(const Quaternion& q) noexcept;

	// static functions
	public:
		static Quaternion		rotationQuaternion(const Float4& axis, float angle) noexcept;

		// q^(-1)
		static Quaternion		reciprocal(const Quaternion& q) noexcept;

	private:
		Float4					_data;
	};

	// alias
	using quaternion = Quaternion;
}


// === HEADER ENDS ===
#endif // !FS_FLOAT4_H
