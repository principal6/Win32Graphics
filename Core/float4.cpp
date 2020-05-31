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
		return Float4(_mm_add_ps(_data, b._data));
	}

	Float4 Float4::operator-(const Float4& b) const
	{
		return Float4(_mm_sub_ps(_data, b._data));
	}

	Float4 Float4::operator*(const Float4& b) const
	{
		return Float4(_mm_mul_ps(_data, b._data));
	}

	Float4 Float4::operator/(const Float4& b) const
	{
		return Float4(_mm_div_ps(_data, b._data));
	}

	Float4 Float4::operator*(float s) const
	{
		return Float4(_mm_mul_ps(_data, _mm_set_ps(s, s, s, s)));
	}

	Float4 Float4::operator/(float s) const
	{
		return Float4(_mm_div_ps(_data, _mm_set_ps(s, s, s, s)));
	}

	Float4 Float4::operator==(const Float4& b) const noexcept
	{
		return Float4(_mm_cmpeq_ps(_data, b._data));
	}

	Float4 Float4::operator!=(const Float4& b) const noexcept
	{
		return Float4(_mm_cmpneq_ps(_data, b._data));
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

	Quaternion Float4::asQuaternion() const noexcept
	{
		return Quaternion(0, getX(), getY(), getZ());
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
		return Float4(result);
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


	Quaternion::Quaternion()
	{
		__noop;
	}

	Quaternion::Quaternion(float a, float b, float c, float d) : _data{ a, b, c, d }
	{
		__noop;
	}

	Quaternion::Quaternion(const Quaternion& q) : _data{ q._data }
	{
		__noop;
	}

	Quaternion::Quaternion(const Float4& v) : _data{ v }
	{
		__noop;
	}

	Quaternion::~Quaternion()
	{
		__noop;
	}

	Quaternion Quaternion::operator*(const Quaternion& q) const noexcept
	{
		const float a1 = this->getA();
		const float b1 = this->getB();
		const float c1 = this->getC();
		const float d1 = this->getD();

		const float a2 = q.getA();
		const float b2 = q.getB();
		const float c2 = q.getC();
		const float d2 = q.getD();

		return Quaternion
		(
			+ a1 * a2 - b1 * b2 - c1 * c2 - d1 * d2,
			+ a1 * b2 + b1 * a2 + c1 * d2 - d1 * c2, // i
			+ a1 * c2 - b1 * d2 + c1 * a2 + d1 * b2, // j
			+ a1 * d2 + b1 * c2 - c1 * b2 + d1 * a2  // k
		);
	}

	Float4 Quaternion::asFloat4() const noexcept
	{
		return Float4(getB(), getC(), getD(), 1);
	}

	Quaternion Quaternion::reciprocal() const noexcept
	{
		return Quaternion::reciprocal(*this);
	}

	float Quaternion::getA() const noexcept
	{
		return _data.getX();
	}

	float Quaternion::getB() const noexcept
	{
		return _data.getY();
	}

	float Quaternion::getC() const noexcept
	{
		return _data.getZ();
	}

	float Quaternion::getD() const noexcept
	{
		return _data.getW();
	}

	Quaternion Quaternion::conjugate(const Quaternion& q) noexcept
	{
		const float a = q.getA();
		const float b = q.getB();
		const float c = q.getC();
		const float d = q.getD();

		return Quaternion(a, -b, -c, -d);
	}

	float Quaternion::norm(const Quaternion& q) noexcept
	{
		return Float4::length(q._data);
	}

	Quaternion Quaternion::reciprocal(const Quaternion& q) noexcept
	{
		const Quaternion conjugate = Quaternion::conjugate(q);
		const float norm = Quaternion::norm(q);
		return Quaternion(conjugate._data / (norm * norm));
	}

	Quaternion Quaternion::rotationQuaternion(const Float4& axis, float angle) noexcept
	{
		const Float4 r = Float4::normalize(axis);
		const float half_angle = angle * 0.5f;
		const float cos_half = cosf(half_angle);
		const float sin_half = sinf(half_angle);
		return Quaternion(cos_half, sin_half * r.getX(), sin_half * r.getY(), sin_half * r.getZ());
	}
}
