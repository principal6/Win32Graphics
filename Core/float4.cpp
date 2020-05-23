#include "pch.h"
#include "Float4.h"


namespace fs
{
	Float4::Float4()
	{
		_data = _mm_setzero_ps();
	}

	Float4::Float4(float x, float y, float z, float w)
	{
		set(x, y, z, w);
	}

	Float4::Float4(const __m128& m)
	{
		_data = m;
	}

	Float4::Float4(const Float4& b)
	{
		_data = b._data;
	}

	Float4::Float4(Float4&& b) noexcept
	{
		_data = std::move(b._data);
	}

	Float4::~Float4()
	{
	}

	Float4& Float4::operator=(const Float4& b)
	{
		if (this == &b)
		{
			return *this;
		}
		_data = b._data;
		return *this;
	}

	Float4& Float4::operator=(Float4&& b) noexcept
	{
		if (this == &b)
		{
			return *this;
		}
		_data = std::move(b._data);
		return *this;
	}

	Float4& Float4::operator+=(const Float4& b)
	{
		_data = _mm_add_ps(_data, b._data);
		return *this;
	}

	Float4& Float4::operator-=(const Float4& b)
	{
		_data = _mm_sub_ps(_data, b._data);
		return *this;
	}

	Float4& Float4::operator*=(const Float4& b)
	{
		_data = _mm_mul_ps(_data, b._data);
		return *this;
	}

	Float4& Float4::operator/=(const Float4& b)
	{
		_data = _mm_div_ps(_data, b._data);
		return *this;
	}

	Float4& Float4::operator*=(float s)
	{
		_data = _mm_mul_ps(_data, _mm_set_ps(s, s, s, s));
		return *this;
	}

	Float4& Float4::operator/=(float s)
	{
		_data = _mm_div_ps(_data, _mm_set_ps(s, s, s, s));
		return *this;
	}

	Float4 Float4::operator+(const Float4& b) const
	{
		return _mm_add_ps(_data, b._data);
	}

	Float4 Float4::operator-(const Float4& b) const
	{
		return _mm_sub_ps(_data, b._data);
	}

	Float4 Float4::operator*(const Float4& b) const
	{
		return _mm_mul_ps(_data, b._data);
	}

	Float4 Float4::operator/(const Float4& b) const
	{
		return _mm_div_ps(_data, b._data);
	}

	Float4 Float4::operator*(float s) const
	{
		return _mm_mul_ps(_data, _mm_set_ps(s, s, s, s));
	}

	Float4 Float4::operator/(float s) const
	{
		return _mm_div_ps(_data, _mm_set_ps(s, s, s, s));
	}

	Float4 Float4::operator==(const Float4& b) const noexcept
	{
		return _mm_cmpeq_ps(_data, b._data);
	}

	Float4 Float4::operator!=(const Float4& b) const noexcept
	{
		return _mm_cmpneq_ps(_data, b._data);
	}

	void Float4::set(float x, float y, float z, float w)
	{
		_data = _mm_set_ps(w, z, y, x);
	}

	void Float4::setX(float s) noexcept
	{
		_data.m128_f32[0] = s;
	}

	void Float4::setY(float s) noexcept
	{
		_data.m128_f32[1] = s;
	}

	void Float4::setZ(float s) noexcept
	{
		_data.m128_f32[2] = s;
	}

	void Float4::setW(float s) noexcept
	{
		_data.m128_f32[3] = s;
	}

	float Float4::get(uint32 index) const noexcept
	{
		return _data.m128_f32[index];
	}

	float Float4::getX() const noexcept
	{
		return _data.m128_f32[0];
	}

	float Float4::getY() const noexcept
	{
		return _data.m128_f32[1];
	}

	float Float4::getZ() const noexcept
	{
		return _data.m128_f32[2];
	}

	float Float4::getW() const noexcept
	{
		return _data.m128_f32[3];
	}

	float Float4::dot(const Float4& a, const Float4& b) noexcept
	{
		__m128 result{ _mm_mul_ps(a._data, b._data) };
		return (result.m128_f32[0] + result.m128_f32[1] + result.m128_f32[2] + result.m128_f32[3]);
	}

	Float4 Float4::cross(const Float4& a, const Float4& b) noexcept
	{
		__m128 result
		{
			a.getY() * b.getZ() - a.getZ() * b.getY(),
			a.getZ() * b.getX() - a.getX() * b.getZ(),
			a.getX() * b.getY() - a.getY() * b.getX(),
			0,
		};
		return result;
	}

	float Float4::length(const Float4& a) noexcept
	{
		return sqrtf(Float4::dot(a, a));
	}

	Float4 Float4::normalize(const Float4& a) noexcept
	{
		float length{ Float4::length(a) };
		return (a / length);
	}
}
