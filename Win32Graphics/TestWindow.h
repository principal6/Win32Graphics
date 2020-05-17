#pragma once

#include "IGraphicalWindow.h"


namespace fs
{
	class TestWindow : public IGraphicalWindow
	{
	public:
		TestWindow(float width, float height);
		virtual ~TestWindow();

	public:
		virtual void set(const std::wstring& title, HINSTANCE hInstance, WNDPROC windowProc) override;
	};
}
