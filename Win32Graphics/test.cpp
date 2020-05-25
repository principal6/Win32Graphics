#include <Core/pch.h>
#include "Line3DWindow.h"


static constexpr float g_kWidth{ 800 };
static constexpr float g_kHeight{ 600 };
static fs::Line3DWindow g_Line3DWindow{ g_kWidth, g_kHeight };

LRESULT WINAPI WinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return g_Line3DWindow.processWindowProc(hWnd, Msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	using namespace fs;

	g_Line3DWindow.set(L"Test Window", hInstance, WinProc);

	g_Line3DWindow.addFont(L"Consolas", 20, false);

	static constexpr Color clearColor{ 0.875f, 0.875f, 1.0f };

	g_Line3DWindow.setProjectionMatrix(3.14f / 3.0f, 0.1f, 10.0f);

	// front
	g_Line3DWindow.addLine(float4(-0.5f, +0.5f, +0.5f, 1), float4(+0.5f, +0.5f, +0.5f, 1), Color(1.0f, 0, 0));
	g_Line3DWindow.addLine(float4(+0.5f, +0.5f, +0.5f, 1), float4(+0.5f, -0.5f, +0.5f, 1), Color(1.0f, 0, 0));
	g_Line3DWindow.addLine(float4(-0.5f, -0.5f, +0.5f, 1), float4(+0.5f, -0.5f, +0.5f, 1), Color(1.0f, 0, 0));
	g_Line3DWindow.addLine(float4(-0.5f, +0.5f, +0.5f, 1), float4(-0.5f, -0.5f, +0.5f, 1), Color(1.0f, 0, 0));

	// back
	g_Line3DWindow.addLine(float4(-0.5f, +0.5f, -0.5f, 1), float4(+0.5f, +0.5f, -0.5f, 1), Color(0, 0, 1.0f));
	g_Line3DWindow.addLine(float4(+0.5f, +0.5f, -0.5f, 1), float4(+0.5f, -0.5f, -0.5f, 1), Color(0, 0, 1.0f));
	g_Line3DWindow.addLine(float4(-0.5f, -0.5f, -0.5f, 1), float4(+0.5f, -0.5f, -0.5f, 1), Color(0, 0, 1.0f));
	g_Line3DWindow.addLine(float4(-0.5f, +0.5f, -0.5f, 1), float4(-0.5f, -0.5f, -0.5f, 1), Color(0, 0, 1.0f));

	// sides
	g_Line3DWindow.addLine(float4(-0.5f, +0.5f, +0.5f, 1), float4(-0.5f, +0.5f, -0.5f, 1), Color(0, 1.0f, 0));
	g_Line3DWindow.addLine(float4(+0.5f, +0.5f, +0.5f, 1), float4(+0.5f, +0.5f, -0.5f, 1), Color(0, 1.0f, 0));
	g_Line3DWindow.addLine(float4(-0.5f, -0.5f, +0.5f, 1), float4(-0.5f, -0.5f, -0.5f, 1), Color(0, 1.0f, 0));
	g_Line3DWindow.addLine(float4(+0.5f, -0.5f, +0.5f, 1), float4(+0.5f, -0.5f, -0.5f, 1), Color(0, 1.0f, 0));

	// world translation
	g_Line3DWindow.translate(0, 0, -2.0f);

	while (g_Line3DWindow.update() == true)
	{
		if (g_Line3DWindow.tickInput() == true)
		{
			if (g_Line3DWindow.isKeyPressed(VK_ESCAPE) == true)
			{
				break;
			}

			if (g_Line3DWindow.isKeyDown(VK_RIGHT) == true)
			{
				g_Line3DWindow.rotateAxisAngle(float4(1, 2, -1, 0), +0.05f);
			}

			if (g_Line3DWindow.isKeyDown(VK_LEFT) == true)
			{
				g_Line3DWindow.rotateAxisAngle(float4(1, 2, -1, 0), -0.05f);
			}
		}
		
		g_Line3DWindow.beginRendering(clearColor);
		{
			g_Line3DWindow.useFont(0);

			g_Line3DWindow.drawTextToScreen(Position2(100, 0), L"Test Window", Color(0.75f, 0.25f, 0.25f));

			g_Line3DWindow.drawTextToScreen(Position2(300, 0), L"FPS: " + g_Line3DWindow.getFpsWstring(), Color(0, 0.25f, 0.25f));

			g_Line3DWindow.drawLines();

		}
		g_Line3DWindow.endRendering();
	}
	return 0;
}
