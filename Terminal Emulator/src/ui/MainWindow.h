#pragma once

#include "../App.h"


namespace Ui::MainWindow
{
	extern LPCTSTR wclass_name;

	extern HWND handle;

	void Create(LPCTSTR title = nullptr, std::function<void(HWND)> after = nullptr);

	void Destroy();

	LRESULT CALLBACK WndProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param);
}

namespace Ui::MainWindow::MessageHandlers
{
	void Close(HWND window);

	void Create(HWND window);

	void Destroy(HWND window);

	void NCActivate(HWND window,BOOL active,HRGN region);

	void NCPaint(HWND window, HRGN region);

	void EraseBackground(HWND window, HDC context);

	void Paint(HWND window);
}