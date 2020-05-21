#include "pch.h"
#include "float4.h"


namespace fs
{
	Float4::Float4()
	{
		_data.m = _mm_setzero_ps();
	}

	Float4::Float4(float x, float y, float z, float w)
	{
		set(x, y, z, w);
	}

	Float4::Float4(const __m128& m)
	{
		_data.m = m;
	}

	Float4::Float4(const Float4& b)
	{
		_data.m = b._data.m;
	}

	Float4::Float4(Float4&& b) noexcept
	{
		if (this == &b) return;
		_data.m = std::move(b._data.m);
	}

	Float4::~Float4()
	{
	}

	Float4& Float4::operator=(const Float4& b)
	{
		_data.m = b._data.m;
		return *this;
	}

	Float4& Float4::operator=(Float4&& b) noexcept
	{
		if (this == &b) return *this;
		_data.m = std::move(b._data.m);
		return *this;
	}

	Float4& Float4::operator+=(const Float4& b)
	{
		_data.m = _mm_add_ps(_data.m, b._data.m);
		return *this;
	}

	Float4& Float4::operator-=(const Float4& b)
	{
		_data.m = _mm_sub_ps(_data.m, b._data.m);
		return *this;
	}

	Float4& Float4::operator*=(const Float4& b)
	{
		_data.m = _mm_mul_ps(_data.m, b._data.m);
		return *this;
	}

	Float4& Float4::operator/=(const Float4& b)
	{
		_data.m = _mm_div_ps(_data.m, b._data.m);
		return *this;
	}

	Float4& Float4::operator*=(float s)
	{
		_data.m = _mm_mul_ps(_data.m, _mm_set_ps(s, s, s, s));
		return *this;
	}

	Float4& Float4::operator/=(float s)
	{
		_data.m = _mm_div_ps(_data.m, _mm_set_ps(s, s, s, s));
		return *this;
	}

	Float4 Float4::operator+(const Float4& b) const
	{
		return _mm_add_ps(_data.m, b._data.m);
	}

	Float4 Float4::operator-(const Float4& b) const
	{
		return _mm_sub_ps(_data.m, b._data.m);
	}

	Float4 Float4::operator*(const Float4& b) const
	{
		return _mm_mul_ps(_data.m, b._data.m);
	}

	Float4 Float4::operator/(const Float4& b) const
	{
		return _mm_div_ps(_data.m, b._data.m);
	}

	Float4 Float4::operator*(float s) const
	{
		return _mm_mul_ps(_data.m, _mm_set_ps(s, s, s, s));
	}

	Float4 Float4::operator/(float s) const
	{
		return _mm_div_ps(_data.m, _mm_set_ps(s, s, s, s));
	}

	Float4 Float4::operator==(const Float4& b) const noexcept
	{
		return _mm_cmpeq_ps(_data.m, b._data.m);
	}

	Float4 Float4::operator!=(const Float4& b) const noexcept
	{
		return _mm_cmpneq_ps(_data.m, b._data.m);
	}

	void Float4::set(float x, float y, float z, float w)
	{
		_data.m = _mm_set_ps(w, z, y, x);
	}

	void Float4::setX(float s) noexcept
	{
		_data.x = s;
	}

	void Float4::setY(float s) noexcept
	{
		_data.y = s;
	}

	void Float4::setZ(float s) noexcept
	{
		_data.z = s;
	}

	void Float4::setW(float s) noexcept
	{
		_data.w = s;
	}

	float Float4::getX() const noexcept
	{
		return _data.x;
	}

	float Float4::getY() const noexcept
	{
		return _data.y;
	}

	float Float4::getZ() const noexcept
	{
		return _data.z;
	}

	float Float4::getW() const noexcept
	{
		return _data.w;
	}
}