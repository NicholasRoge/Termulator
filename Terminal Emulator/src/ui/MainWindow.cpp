#include "MainWindow.h"

#include "../Util.h"

#include <system_error>
#include <tchar.h>
#include <Uxtheme.h>

using namespace Ui::MainWindow;

namespace Ui::MainWindow
{
	/* Prototypes */
	void CreateWindowClass();
	
	void CreateWindowHandle(LPCTSTR title);

	void DestroyWindowClass();

	void DestroyWindowHandle();

	/* Variable Definitions */
	HWND  handle = nullptr;

	HBRUSH bgcolor = nullptr;

	LPCTSTR wclass_name = L"MainWindow";


	void Create(LPCTSTR title, std::function<void(HWND)> after)
	{
		bgcolor = CreateSolidBrush(RGB(48, 48, 48));

		CreateWindowClass();
		CreateWindowHandle(title);

		if (after)
		{
			after(handle);
		}
	}

	void CreateWindowHandle(LPCTSTR title)
	{
		DWORD style = 0;
		style |= WS_OVERLAPPEDWINDOW;

		DWORD style_ex = 0;

		handle = CreateWindowEx(
			style_ex,
			wclass_name,
			title ? title : L"Untitled Window",
			style,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			nullptr,
			nullptr,
			GetModuleHandle(nullptr),
			nullptr
		);
		if (!handle)
		{
			throw WindowsException();
		}
	}
	
	void CreateWindowClass()
	{
		WNDCLASSEX wclass;
		wclass.cbSize = sizeof(wclass);
		wclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wclass.lpfnWndProc = WndProc;
		wclass.cbClsExtra = 0;
		wclass.cbWndExtra = 0;
		wclass.hInstance = GetModuleHandle(nullptr);
		wclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wclass.hbrBackground = nullptr;
		wclass.lpszMenuName = nullptr;
		wclass.lpszClassName = wclass_name;
		wclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		if (!RegisterClassEx(&wclass))
		{
			throw WindowsException();
		}
	}

	void Destroy()
	{
		DestroyWindowHandle();
		DestroyWindowClass();

		DeleteObject(bgcolor);
	}

	void DestroyWindowHandle()
	{
		DestroyWindow(handle);
	}

	void DestroyWindowClass()
	{
		UnregisterClass(wclass_name, GetModuleHandle(nullptr));
	}
	
	LRESULT CALLBACK WndProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
	{
		switch(message)
		{
			case WM_CLOSE:
				MessageHandlers::Close(window);
				break;

			case WM_DESTROY:
				MessageHandlers::Destroy(window);
				break;

			case WM_NCACTIVATE:
				MessageHandlers::NCActivate(window, (BOOL)w_param, (HRGN)l_param);
				return TRUE;

			case WM_NCPAINT:
				MessageHandlers::NCPaint(window, (HRGN)w_param);
				break;

			case WM_ERASEBKGND:
				MessageHandlers::EraseBackground(window, (HDC)w_param);
				return 1;

			case WM_PAINT:
				MessageHandlers::Paint(window);
				break;
		}

		return DefWindowProc(window, message, w_param, l_param);
	}
}

namespace Ui::MainWindow::MessageHandlers
{
	void Close(HWND window)
	{
		DestroyWindow(window);
	}
	
	void Create(HWND window)
	{

	}

	void Destroy(HWND window)
	{
		PostQuitMessage(0);
	}

	void NCActivate(HWND window, BOOL active, HRGN region)
	{
	}

	void NCPaint(HWND window, HRGN region)
	{
		HDC context;
		context = GetWindowDC(window);
		auto error = GetLastError();

		RECT rect;
		GetWindowRect(window, &rect);
		rect.right -= rect.left;
		rect.left = 0;
		rect.bottom -= rect.top;
		rect.top = 0;
		FillRect(context, &rect, bgcolor);

		ReleaseDC(window, context);
	}

	void EraseBackground(HWND window, HDC context)
	{
		if (!bgcolor)
		{
			return;
		}

		RECT rect;
		GetClientRect(window, &rect);
		FillRect(context, &rect, bgcolor);
	}

	void Paint(HWND window)
	{
		PAINTSTRUCT ps;
		auto context = BeginPaint(window, &ps);

		RECT rect;
		GetClientRect(window, &rect);
		SetTextColor(context, RGB(240, 240, 240));
		SetBkMode(context, TRANSPARENT);
		DrawText(context, L"Oh, hai!", 9, &rect, 0);

		EndPaint(window, &ps);
	}
}