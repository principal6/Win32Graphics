#pragma once


#ifndef FS_I_WIN32_GDI_WINDOW_H
#define FS_I_WIN32_GDI_WINDOW_H
// === HEADER BEGINS ===


#include <Core/_CommonTypes.h>
#include <Utilities/Timer.h>

#include <string>


namespace fs
{
	struct Float2
	{
		constexpr Float2()
		{
			__noop;
		}
		constexpr Float2(float x_, float y_) : x{ x_ }, y{ y_ }
		{
			__noop;
		}

		float x{};
		float y{};

		constexpr bool operator==(const Float2& b) const
		{
			return (x == b.x && y == b.y);
		}
		constexpr bool operator!=(const Float2& b) const
		{
			return !(*this == b);
		}

		constexpr Float2 operator+() const
		{
			return Float2(+x, +y);
		}
		constexpr Float2 operator-() const
		{
			return Float2(-x, -y);
		}

		constexpr Float2 operator+(const Float2& b) const
		{
			return Float2(x + b.x, y + b.y);
		}
		constexpr Float2 operator-(const Float2& b) const
		{
			return Float2(x - b.x, y - b.y);
		}
		constexpr Float2 operator*(const Float2& b) const
		{
			return Float2(x * b.x, y * b.y);
		}
	};
	using Position2 = Float2;
	using Size2 = Float2;
	

	struct Color
	{
		constexpr Color()
		{
			__noop;
		}
		constexpr Color(float r_, float g_, float b_) : r{ r_ }, g{ g_ }, b{ b_ }
		{
			__noop;
		}

		float r{};
		float g{};
		float b{};

		// clamped addition
		constexpr void add(const Color& o)
		{
			r = min(r + o.r, 1.0f);
			g = min(g + o.g, 1.0f);
			b = min(b + o.b, 1.0f);
		}
		// clamped substraction
		constexpr void sub(const Color& o)
		{
			r = max(r - o.r, 0);
			g = max(g - o.g, 0);
			b = max(b - o.b, 0);
		}

		// clamped addition
		static constexpr Color add(const Color& a, const Color& o)
		{
			return Color(min(a.r + o.r, 1.0f), min(a.g + o.g, 1.0f), min(a.b + o.b, 1.0f));
		}
		// clamped substraction
		static constexpr Color sub(const Color& a, const Color& o)
		{
			return Color(max(a.r - o.r, 0), max(a.g - o.g, 0), max(a.b - o.b, 0));
		}

		constexpr Color operator+(const Color& o) const
		{
			return Color(r + o.r, g + o.g, b + o.b);
		}
		constexpr Color operator-(const Color& o) const
		{
			return Color(r - o.r, g - o.g, b - o.b);
		}

		constexpr Color& operator+=(const Color& o)
		{
			r += o.r;
			g += o.g;
			b += o.b;
			return *this;
		}
		constexpr Color& operator-=(const Color& o)
		{
			r -= o.r;
			g -= o.g;
			b -= o.b;
			return *this;
		}
	};


	struct Image
	{
		Image()
		{
			__noop;
		}
		Image(HBITMAP bitmap_, const Size2& size_) : bitmap{ bitmap_ }, size{ size_ }
		{
			__noop;
		}
		HBITMAP	bitmap{};
		Size2	size{};
	};


	enum class EHorzAlign
	{
		Left,
		Center,
		Right
	};

	enum class EVertAlign
	{
		Top,
		Center,
		Bottom,
	};


	class IWin32GdiWindow
	{
	public:
		IWin32GdiWindow(float width, float height);
		virtual ~IWin32GdiWindow();

	public:
		// @주의: override한 set() 안에서 반드시 setInternal()를 가장 먼저 호출하세요.
		virtual void set(const std::wstring& title, HINSTANCE hInstance, WNDPROC windowProc) abstract;

	protected:
		// @주의: override한 set() 안에서 이 함수를 반드시 가장 먼저 호출하세요.
		void setInternal(const std::wstring& title, HINSTANCE hInstance, WNDPROC windowProc);

	public:
		LRESULT processWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

	public:
		void addFont(const std::wstring& fontName, int32 size, bool isKorean);
		void useFont(uint32 fontIndex) const noexcept;

		// image의 index를 리턴함.
		uint32 createImageFromFile(const std::wstring& fileName);

		// image의 index를 리턴함.
		uint32 createBlankImage(const Size2& size);

	public:
		virtual bool update();

	public:
		void beginRendering(const Color& clearColor) const noexcept;
		void endRendering() const noexcept;

	public:
		// 이 함수를 직접 호출하기보단, createBlankImage()와 drawRectangleToImage()를 이용하면 훨씬 성능에 좋습니다.
		void drawRectangleToScreen(const Position2& position, const Size2& size, const Color& color, uint8 alpha = 255) const noexcept;

		// createBlankImage(), drawImage...()와 함께 사용하면 drawRectangleToScreen()보다 더 좋은 성능을 낼 수 있는 함수입니다.
		void drawRectangleToImage(uint32 imageIndex, const Position2& position, const Size2& size, const Color& color, uint8 alpha = 255);

		void drawImageToScreen(uint32 imageIndex, const Position2& position) const noexcept;
		void drawImageAlphaToScreen(uint32 imageIndex, const Position2& position) const noexcept;
		void drawImageAlphaToScreen(uint32 imageIndex, const Position2& position, uint8 alpha) const noexcept;
		void drawImagePrecomputedAlphaToScreen(uint32 imageIndex, const Position2& position) const noexcept;
		void drawTextToScreen(const Position2& position, const std::wstring& content, const Color& color) const noexcept;
		void drawTextToScreen(const Position2& position, const Size2& area, const std::wstring& content, const Color& color,
			EHorzAlign eHorzAlign, EVertAlign eVertAlign) const noexcept;
		void drawLineToScreen(const Position2& positionA, const Position2& positionB, const Color& color) const noexcept;
		void drawLineToScreenNormalized(const Position2& positionA, const Position2& positionB, const Color& color) const noexcept;

	public:
		uint32 getFps() const noexcept;
		const std::wstring& getFpsWstring() const noexcept;
		float getWidth() const noexcept;
		float getHeight() const noexcept;
		bool tickInput() const noexcept;
		bool isKeyPressed(int keyCode) const noexcept;
		bool isKeyDown(int keyCode) const noexcept;
		bool tickSecond() const noexcept;

	private:
		// 필요한 변수들을 초기화하고, 리소스를 할당한다.
		void initialize();

		// 사용한 리소스를 해제한다.
		void uninitialize();

	protected:
		static constexpr uint32	kFpsBufferSize{ 20 };
		const float				kWidth{ 800 };
		const float				kHeight{ 600 };

	private:
		HWND					_hWnd{};
		HDC						_frontDc{};
		HDC						_backDc{};
		HBITMAP					_backDcBitmap{};
		HDC						_tempDc{};

	private:
		std::vector<HFONT>		_vFonts{};
		std::vector<Image>		_vImages{};

	private:
		Timer					_secondTimer{};
		mutable uint32			_frameCount{};
		uint32					_fps{};
		std::wstring			_fpsWstring{};
		mutable bool			_bSecondTick{ false };

	private:
		Timer					_inputTimer{};
		mutable bool			_bInputTick{ false };
	};
}


// === HEADER ENDS ===
#endif // !FS_IWIN32_GDI_WINDOW_H
