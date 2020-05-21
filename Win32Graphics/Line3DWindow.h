#pragma once


#ifndef FS_LINE_3D_WINDOW_H
#define FS_LINE_3D_WINDOW_H
// === HEADER BEGINS ===


#include <Core/IWin32GdiWindow.h>
#include <Core/float4.h>
#include <Core/float4x4.h>


namespace fs
{
	class Line3DWindow final : public IWin32GdiWindow
	{
	public:
		Line3DWindow(float width, float height);
		virtual ~Line3DWindow();

	public:
		virtual void set(const std::wstring& title, HINSTANCE hInstance, WNDPROC windowProc) override;

	public:
		// right-handed
		void setProjectionMatrix(float Fov, float nearZ, float farZ, float ratio = 1.0f) noexcept;
		void translate(float x, float y, float z) noexcept;
		void scale(float x, float y, float z) noexcept;
		void rotateAroundXAxis(float angle) noexcept;

	public:
		void addLine(const float4& positionA, const float4& positionB, const Color& color) noexcept;
		void drawLines() const noexcept;

	private:
		float4x4			_projectionMatrix;
		float4x4			_translationMatrix;
		float4x4			_rotationMatrix;
		float4x4			_scalingMatrix;
		std::vector<float4>	_vVertices;
		std::vector<Color>	_vLineColors;
	};
}


// === HEADER EDNS ===
#endif // !FS_LINE_3D_WINDOW_H
