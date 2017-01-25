#include "App.h"

#include "Ui.h"


namespace App
{
	/* Prototypes */
	void RunMessagePump();

	/* Definitions */
	InitCallback      Init      = nullptr;
	TerminateCallback Terminate = nullptr;

	int exit_code = 0;
	

	int Main()
	{
		try
		{
			Ui::Init();

			if (Init)
			{
				Init();
			}

			RunMessagePump();

			if (Terminate)
			{
				Terminate();
			}

			Ui::Terminate();

			return GetExitCode();
		}
		catch(std::exception& e)
		{
			MessageBoxA(nullptr, e.what(), "An Exception Has Occured", MB_OK);

			return 1;
		}
	}

	void RunMessagePump()
	{
		MSG message;


		while (true) 
		{ 
			if (!PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
			{
				continue;
			}

			if (message.message == WM_QUIT)
			{
				break;
			} 
			else 
			{
				TranslateMessage(&message); 
				DispatchMessage(&message); 
			}
		}
	 
		SetExitCode(message.wParam); 
	}

	int GetExitCode()
	{
		return exit_code;
	}

	void SetExitCode(int exit_code)
	{
		App::exit_code = exit_code;
	}
}
