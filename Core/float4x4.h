#pragma once


#ifndef FS_FLOAT4X4_H
#define FS_FLOAT4X4_H
// === HEADER BEGINS ===


#include <Core/Float4.h>


namespace fs
{
	// 2x2 matrix
	struct Float2x2
	{
		Float2x2()
		{
			setIdentity();
		}
		Float2x2(float m00, float m01, float m10, float m11) : m{ m00, m01, m10, m11 }
		{
			__noop;
		}

		float m[2][2]{};

		Float2x2 operator*(float s) const noexcept
		{
			return Float2x2(
				m[0][0] * s, m[0][1] * s,
				m[1][0] * s, m[1][1] * s
			);
		}

		Float2x2 operator/(float s) const noexcept
		{
			return Float2x2(
				m[0][0] / s, m[0][1] / s,
				m[1][0] / s, m[1][1] / s
			);
		}

		void setZero() noexcept
		{
			memset(m, 0, sizeof(float) * 4);
		}

		void setIdentity() noexcept
		{
			setZero();

			m[0][0] = 1;
			m[1][1] = 1;
		}

		float determinant() const noexcept
		{
			float a = m[0][0];
			float b = m[0][1];
			float c = m[1][0];
			float d = m[1][1];

			return a * d - b * c;
		}

		Float2x2 inverse() const noexcept
		{
			const float a = m[0][0];
			const float b = m[0][1];
			const float c = m[1][0];
			const float d = m[1][1];

			return Float2x2(
				d, -b,
				-c, a
			) / determinant();
		}
	};

	// 3x3 matrix
	struct Float3x3
	{
		Float3x3()
		{
			setIdentity();
		}
		Float3x3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22) :
			m{ m00, m01, m02, m10, m11, m12, m20, m21, m22 }
		{
			__noop;
		}

		float m[3][3]{};

		Float3x3 operator*(const Float3x3& r) const noexcept
		{
			return Float3x3
			(
				// row 0
				m[0][0] * r.m[0][0] + m[0][1] * r.m[1][0] + m[0][2] * r.m[2][0], 
				m[0][0] * r.m[0][1] + m[0][1] * r.m[1][1] + m[0][2] * r.m[2][1],
				m[0][0] * r.m[0][2] + m[0][1] * r.m[1][2] + m[0][2] * r.m[2][2],

				// row 1
				m[1][0] * r.m[0][0] + m[1][1] * r.m[1][0] + m[1][2] * r.m[2][0],
				m[1][0] * r.m[0][1] + m[1][1] * r.m[1][1] + m[1][2] * r.m[2][1],
				m[1][0] * r.m[0][2] + m[1][1] * r.m[1][2] + m[1][2] * r.m[2][2],

				// row 2
				m[2][0] * r.m[0][0] + m[2][1] * r.m[1][0] + m[2][2] * r.m[2][0],
				m[2][0] * r.m[0][1] + m[2][1] * r.m[1][1] + m[2][2] * r.m[2][1],
				m[2][0] * r.m[0][2] + m[2][1] * r.m[1][2] + m[2][2] * r.m[2][2]
			);
		}

		Float3x3 operator*(float s) const noexcept
		{
			return Float3x3(
				m[0][0] * s, m[0][1] * s, m[0][2] * s,
				m[1][0] * s, m[1][1] * s, m[1][2] * s,
				m[2][0] * s, m[2][1] * s, m[2][2] * s
			);
		}

		Float3x3 operator/(float s) const noexcept
		{
			return Float3x3(
				m[0][0] / s, m[0][1] / s, m[0][2] / s,
				m[1][0] / s, m[1][1] / s, m[1][2] / s,
				m[2][0] / s, m[2][1] / s, m[2][2] / s
			);
		}

		void setZero() noexcept
		{
			memset(m, 0, sizeof(float) * 9);
		}

		void setIdentity() noexcept
		{
			setZero();

			m[0][0] = 1;
			m[1][1] = 1;
			m[2][2] = 1;
		}

		Float2x2 minor(uint32 rowIndex, uint32 columnIndex) const noexcept
		{
			Float2x2 result;

			uint32 smallY{};
			for (uint32 y = 0; y < 3; ++y)
			{
				if (y == rowIndex) continue;

				uint32 smallX{};
				for (uint32 x = 0; x < 3; ++x)
				{
					if (x == columnIndex) continue;

					result.m[smallY][smallX] = m[y][x];

					++smallX;
				}

				++smallY;
			}

			return result;
		}

		float determinant() const noexcept
		{
			float a = m[0][0];
			float b = m[0][1];
			float c = m[0][2];

			return a * minor(0, 0).determinant() - b * minor(0, 1).determinant() + c * minor(0, 2).determinant();
		}

		Float3x3 transpose() const noexcept
		{
			return Float3x3
			(
				m[0][0], m[1][0], m[2][0],
				m[0][1], m[1][1], m[2][1],
				m[0][2], m[1][2], m[2][2]
			);
		}

		Float3x3 cofactor() const noexcept
		{
			return Float3x3
			(
				+minor(0, 0).determinant(), -minor(0, 1).determinant(), +minor(0, 2).determinant(),
				-minor(1, 0).determinant(), +minor(1, 1).determinant(), -minor(1, 2).determinant(),
				+minor(2, 0).determinant(), -minor(2, 1).determinant(), +minor(2, 2).determinant()
			);
		}

		Float3x3 adjugate() const noexcept
		{
			return cofactor().transpose();
		}

		Float3x3 inverse() const noexcept
		{
			return adjugate() / determinant();
		}
	};

	// SSE (members are Float4)
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
		Float3x3				minor(uint32 rowIndex, uint32 columnIndex) const noexcept;
		float					determinant() const noexcept;
		Float4x4				transpose() const noexcept;
		Float4x4				cofactor() const noexcept;
		Float4x4				adjugate() const noexcept;
		Float4x4				inverse() const noexcept;

	public:
		Float4					mul(const Float4& v) const noexcept;
		Float4x4				mul(const Float4x4& m) const noexcept;

	private:
		Float4					_row[4];


	// static functions
	public:
		static Float4			mul(const Float4x4& m, const Float4& v) noexcept;
		static Float4x4			mul(const Float4x4& l, const Float4x4& r) noexcept;

		static Float4x4			translationMatrix(float x, float y, float z) noexcept;
		static Float4x4			scalingMatrix(float x, float y, float z) noexcept;
		static Float4x4			rotationMatrixX(float angle) noexcept;
		static Float4x4			rotationMatrixY(float angle) noexcept;
		static Float4x4			rotationMatrixZ(float angle) noexcept;
		static Float4x4			projectionMatrixPerspective(float Fov, float nearZ, float farZ, float ratio) noexcept;
	};

	// alias
	using float4x4 = Float4x4;
}


// === HEADER ENDS ===
#endif // !FS_FLOAT4X4_H
