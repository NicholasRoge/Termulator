#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "uxtheme.lib")

#include "Ui.h"

#include "./Ui/MainWindow.h"

#include <CommCtrl.h>
#include <Uxtheme.h>


namespace Ui
{
	/* Definitions */
	void Init()
	{
		INITCOMMONCONTROLSEX iccs;
		iccs.dwSize = sizeof(iccs);
		iccs.dwICC = 0;
		InitCommonControlsEx(&iccs);

		MainWindow::Create(L"Termulator", [] (auto handle){
			ShowWindow(handle, SW_SHOWDEFAULT);
			UpdateWindow(handle);
		});
	}

	void Terminate()
	{
		MainWindow::Destroy();
	}
}