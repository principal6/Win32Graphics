#include "Line3DWindow.h"


namespace fs
{
	Line3DWindow::Line3DWindow(float width, float height) : IWin32GdiWindow(width, height)
	{
		_rotationAxis = float4(1, 0, 0, 0);
		_rotationAngle = 0;
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
		_projectionMatrix = float4x4::projectionMatrixPerspective(Fov, nearZ, farZ, ratio);
	}

	void Line3DWindow::translate(float x, float y, float z) noexcept
	{
		_translationMatrix = float4x4::translationMatrix(x, y, z);
	}

	void Line3DWindow::scale(float x, float y, float z) noexcept
	{
		_scalingMatrix = float4x4::scalingMatrix(x, y, z);
	}

	void Line3DWindow::rotateAroundXAxis(float angle) noexcept
	{
		_rotationMatrix = float4x4::rotationMatrixX(angle) * _rotationMatrix;
	}

	void Line3DWindow::rotateAroundYAxis(float angle) noexcept
	{
		_rotationMatrix = float4x4::rotationMatrixY(angle) * _rotationMatrix;
	}

	void Line3DWindow::rotateAroundZAxis(float angle) noexcept
	{
		_rotationMatrix = float4x4::rotationMatrixZ(angle) * _rotationMatrix;
	}

	void Line3DWindow::rotateAxisAngle(const float4& axis, float angle) noexcept
	{
		_rotationAxis = axis;
		_rotationAngle += angle;

		_rotationMatrix = float4x4::rotationMatrixAxisAngle(_rotationAxis, _rotationAngle);
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
				float4 vertexA{ _vVertices[static_cast<uint64>(i) * 2 + 0] };
				float4 vertexB{ _vVertices[static_cast<uint64>(i) * 2 + 1] };

				// SRT world
				//const float4x4 worldMatrix = _translationMatrix * _rotationMatrix * _scalingMatrix;
				//vertexA = worldMatrix * vertexA;
				//vertexB = worldMatrix * vertexB;


				// SRT with Quaternion
				vertexA = _scalingMatrix * vertexA;
				vertexB = _scalingMatrix * vertexB;

				const quaternion q = quaternion::rotationQuaternion(_rotationAxis, _rotationAngle);
				const quaternion qReciprocal = q.reciprocal();
				vertexA = quaternion(q * vertexA.asQuaternion() * qReciprocal).asFloat4();
				vertexB = quaternion(q * vertexB.asQuaternion() * qReciprocal).asFloat4();

				vertexA = _translationMatrix * vertexA;
				vertexB = _translationMatrix * vertexB;


				// behind the eye
				if (vertexA.getZ() > 0 && vertexB.getZ() > 0) continue;

				// project
				vertexA = _projectionMatrix * vertexA;
				vertexB = _projectionMatrix * vertexB;
				if (vertexA.getW() == 0)
				{
					vertexA.setW(1.0f);
				}
				if (vertexB.getW() == 0)
				{
					vertexA.setW(1.0f);

				}
				vertexA /= vertexA.getW();
				vertexB /= vertexB.getW();

				__super::drawLineToScreenNormalized(
					Position2(vertexA.getX(), vertexA.getY()),
					Position2(vertexB.getX(), vertexB.getY()),
					_vLineColors[i]);
			}
		}
	}

}
