#include "TestWindow.h"


static constexpr float g_kWidth{ 800 };
static constexpr float g_kHeight{ 600 };
static fs::TestWindow g_testWindow{ g_kWidth, g_kHeight };

LRESULT WINAPI WinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return g_testWindow.processWindowProc(hWnd, Msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	using namespace fs;

	g_testWindow.set(L"Test Window", hInstance, WinProc);

	g_testWindow.addFont(L"Consolas", 20, false);

	static constexpr Color kDefaultColor{ 255, 255, 255 };
	Color clearColor{ 240, 240, 255 };
	Color normalFontColor{ kDefaultColor };
	
	while (g_testWindow.update() == true)
	{
		if (g_testWindow.tickInput() == true)
		{
			if (g_testWindow.isKeyPressed(VK_ESCAPE) == true)
			{
				break;
			}
		}
		
		g_testWindow.beginRendering(clearColor);
		{
			g_testWindow.useFont(0);

			g_testWindow.drawTextToScreen(Position2(100, 0), L"Test Window", Color(200, 100, 100));

			g_testWindow.drawTextToScreen(Position2(300, 0), L"FPS: " + g_testWindow.getFpsWstring(), Color(0, 100, 100));

			g_testWindow.drawLineToScreenNormalized(Position2(-1, +1), Position2(0, 0), Color(180, 0, 0));

			g_testWindow.drawLineToScreenNormalized(Position2(-1, -1), Position2(0, 0), Color(180, 255, 0));
		}
		g_testWindow.endRendering();
	}
	return 0;
}
