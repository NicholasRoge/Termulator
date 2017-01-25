#pragma once

#include <functional>
#include <Windows.h>


namespace App 
{
	using InitCallback      = std::function<void()>;
	using TerminateCallback = std::function<void()>;


	extern InitCallback      Init;
	extern TerminateCallback Terminate;


	int Main();

	int GetExitCode();

	void SetExitCode(int exit_code);
}
