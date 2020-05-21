#include "Line3DWindow.h"


namespace fs
{
	Line3DWindow::Line3DWindow(float width, float height) : IWin32GdiWindow(width, height)
	{
		__noop;
	}

	Line3DWindow::~Line3DWindow()
	{
	}

	void Line3DWindow::set(const std::wstring& title, HINSTANCE hInstance, WNDPROC windowProc)
	{
		__super::setInternal(title, hInstance, windowProc);
	}

	void Line3DWindow::setProjectionMatrix(float Fov, float nearZ, float farZ, float ratio) noexcept
	{
		float a = 1.0f / (tanf(Fov) * ratio);
		float b = 1.0f / (tanf(Fov));
		float c = (-farZ) / (farZ - nearZ);
		float d = (nearZ * farZ) / (farZ - nearZ);
		float e = -1.0f;

		_projectionMatrix.set(
			a, 0, 0, 0,
			0, b, 0, 0,
			0, 0, c, d,
			0, 0, e, 0);
	}

	void Line3DWindow::translate(float x, float y, float z) noexcept
	{
		float4x4 translationMatrix
		{
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1
		};

		_translationMatrix = translationMatrix;
	}

	void Line3DWindow::scale(float x, float y, float z) noexcept
	{
		float4x4 scalingMatrix
		{
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1
		};

		_scalingMatrix = scalingMatrix;
	}

	void Line3DWindow::rotateAroundXAxis(float angle) noexcept
	{
		float4x4 rotationMatrix
		{
			1, 0			, 0				, 0,
			0, +cosf(angle)	, -sinf(angle)	, 0,
			0, +sinf(angle)	, +cosf(angle)	, 0,
			0, 0			, 0				, 1
		};

		_rotationMatrix = rotationMatrix * _rotationMatrix;
	}

	void Line3DWindow::addLine(const float4& positionA, const float4& positionB, const Color& color) noexcept
	{
		_vVertices.emplace_back(positionA);
		_vVertices.emplace_back(positionB);
		_vLineColors.emplace_back(color);
	}

	void Line3DWindow::drawLines() const noexcept
	{
		if (_vVertices.size() > 0)
		{
			for (uint32 i = 0; i < static_cast<uint32>(_vLineColors.size()); ++i)
			{
				float4 vertexA{ _vVertices[i * 2 + 0] };
				float4 vertexB{ _vVertices[i * 2 + 1] };

				// SRT world
				const float4x4 worldMatrix = _translationMatrix * _rotationMatrix * _scalingMatrix;
				vertexA = worldMatrix.mul(vertexA);
				vertexB = worldMatrix.mul(vertexB);

				if (vertexA.getZ() > 0 && vertexB.getZ() > 0) continue;

				vertexA = _projectionMatrix.mul(vertexA);
				if (vertexA.getW() != 0)
				{
					vertexA /= vertexA.getW();
				}

				vertexB = _projectionMatrix.mul(vertexB);
				if (vertexB.getW() != 0)
				{
					vertexB /= vertexB.getW();
				}

				__super::drawLineToScreenNormalized(
					Position2(vertexA.getX(), vertexA.getY()),
					Position2(vertexB.getX(), vertexB.getY()),
					_vLineColors[i]);
			}
		}
	}

}
