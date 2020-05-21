#include "pch.h"
#include "float4x4.h"


namespace fs
{
	Float4x4::Float4x4()
	{
		setIdentity();
	}

	Float4x4::Float4x4(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13, 
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33) : 
		_row{ 
				{ m00, m01, m02, m03 },
				{ m10, m11, m12, m13 }, 
				{ m20, m21, m22, m23 }, 
				{ m30 ,m31, m32, m33 } 
			}
	{
		__noop;
	}

	Float4x4::Float4x4(const float4& row0, const float4& row1, const float4& row2, const float4& row3)
		: _row{ row0, row1, row2, row3 }
	{
		__noop;
	}

	Float4x4::Float4x4(const Float4x4& b)
	{
		_row[0] = b._row[0];
		_row[1] = b._row[1];
		_row[2] = b._row[2];
		_row[3] = b._row[3];
	}

	Float4x4::Float4x4(Float4x4&& b) noexcept
	{
		if (this == &b) return;
		_row[0] = std::move(b._row[0]);
		_row[1] = std::move(b._row[1]);
		_row[2] = std::move(b._row[2]);
		_row[3] = std::move(b._row[3]);
	}

	Float4x4::~Float4x4()
	{
		__noop;
	}

	Float4x4& Float4x4::operator=(const Float4x4& b)
	{
		_row[0] = b._row[0];
		_row[1] = b._row[1];
		_row[2] = b._row[2];
		_row[3] = b._row[3];
		return *this;
	}

	Float4x4& Float4x4::operator=(Float4x4&& b) noexcept
	{
		if (this == &b) return *this;
		_row[0] = std::move(b._row[0]);
		_row[1] = std::move(b._row[1]);
		_row[2] = std::move(b._row[2]);
		_row[3] = std::move(b._row[3]);
		return *this;
	}

	Float4x4 Float4x4::operator+(const Float4x4& b) const
	{
		return Float4x4(_row[0] + b._row[0], _row[1] + b._row[1], _row[2] + b._row[2], _row[3] + b._row[3]);
	}

	Float4x4 Float4x4::operator-(const Float4x4& b) const
	{
		return Float4x4(_row[0] - b._row[0], _row[1] - b._row[1], _row[2] - b._row[2], _row[3] - b._row[3]);
	}

	Float4x4 Float4x4::operator*(float s) const
	{
		return Float4x4(_row[0] * s, _row[1] * s, _row[2] * s, _row[3] * s);
	}

	Float4x4 Float4x4::operator/(float s) const
	{
		return Float4x4(_row[0] / s, _row[1] / s, _row[2] / s, _row[3] / s);
	}

	Float4x4 Float4x4::operator*(const Float4x4& r) const
	{
		return this->mul(r);
	}

	Float4 Float4x4::operator*(const Float4& v) const
	{
		return this->mul(v);
	}

	void Float4x4::set(float m00, float m01, float m02, float m03, 
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23, 
		float m30, float m31, float m32, float m33)
	{
		_row[0].set(m00, m01, m02, m03);
		_row[1].set(m10, m11, m12, m13);
		_row[2].set(m20, m21, m22, m23);
		_row[3].set(m30, m31, m32, m33);
	}

	void Float4x4::set(const float4& row0, const float4& row1, const float4& row2, const float4& row3)
	{
		_row[0] = row0;
		_row[1] = row1;
		_row[2] = row2;
		_row[3] = row3;
	}

	void Float4x4::setZero()
	{
		_row[0].set(0, 0, 0, 0);
		_row[1].set(0, 0, 0, 0);
		_row[2].set(0, 0, 0, 0);
		_row[3].set(0, 0, 0, 0);
	}

	void Float4x4::setIdentity()
	{
		_row[0].set(1, 0, 0, 0);
		_row[1].set(0, 1, 0, 0);
		_row[2].set(0, 0, 1, 0);
		_row[3].set(0, 0, 0, 1);
	}

	float4 Float4x4::mul(const float4& v) const noexcept
	{
		return float4(
			float4::dot(_row[0], v), // x
			float4::dot(_row[1], v), // y
			float4::dot(_row[2], v), // z
			float4::dot(_row[3], v)  // w
		);
	}

	Float4x4 Float4x4::mul(const Float4x4& m) const noexcept
	{
		float4 col[4]{
			{ m._row[0].getX(), m._row[1].getX(), m._row[2].getX(), m._row[3].getX() },
			{ m._row[0].getY(), m._row[1].getY(), m._row[2].getY(), m._row[3].getY() },
			{ m._row[0].getZ(), m._row[1].getZ(), m._row[2].getZ(), m._row[3].getZ() },
			{ m._row[0].getW(), m._row[1].getW(), m._row[2].getW(), m._row[3].getW() },
		};

		return Float4x4(
			float4::dot(_row[0], col[0]), float4::dot(_row[0], col[1]), float4::dot(_row[0], col[2]), float4::dot(_row[0], col[3]),
			float4::dot(_row[1], col[0]), float4::dot(_row[1], col[1]), float4::dot(_row[1], col[2]), float4::dot(_row[1], col[3]),
			float4::dot(_row[2], col[0]), float4::dot(_row[2], col[1]), float4::dot(_row[2], col[2]), float4::dot(_row[2], col[3]),
			float4::dot(_row[3], col[0]), float4::dot(_row[3], col[1]), float4::dot(_row[3], col[2]), float4::dot(_row[3], col[3])
		);
	}

	Float4x4 Float4x4::mul(const Float4x4& l, const Float4x4& r) noexcept
	{
		float4 rCol[4]{
			{ r._row[0].getX(), r._row[1].getX(), r._row[2].getX(), r._row[3].getX() },
			{ r._row[0].getY(), r._row[1].getY(), r._row[2].getY(), r._row[3].getY() },
			{ r._row[0].getZ(), r._row[1].getZ(), r._row[2].getZ(), r._row[3].getZ() },
			{ r._row[0].getW(), r._row[1].getW(), r._row[2].getW(), r._row[3].getW() },
		};

		return Float4x4(
			float4::dot(l._row[0], rCol[0]), float4::dot(l._row[0], rCol[1]), float4::dot(l._row[0], rCol[2]), float4::dot(l._row[0], rCol[3]),
			float4::dot(l._row[1], rCol[0]), float4::dot(l._row[1], rCol[1]), float4::dot(l._row[1], rCol[2]), float4::dot(l._row[1], rCol[3]),
			float4::dot(l._row[2], rCol[0]), float4::dot(l._row[2], rCol[1]), float4::dot(l._row[2], rCol[2]), float4::dot(l._row[2], rCol[3]),
			float4::dot(l._row[3], rCol[0]), float4::dot(l._row[3], rCol[1]), float4::dot(l._row[3], rCol[2]), float4::dot(l._row[3], rCol[3])
		);
	}

}
