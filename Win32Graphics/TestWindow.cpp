#include "TestWindow.h"


namespace fs
{
	TestWindow::TestWindow(float width, float height) : IGraphicalWindow(width, height)
	{
		__noop;
	}

	TestWindow::~TestWindow()
	{
	}

	void TestWindow::set(const std::wstring& title, HINSTANCE hInstance, WNDPROC windowProc)
	{
		__super::setInternal(title, hInstance, windowProc);


	}

}
