#include "App.h"


/* Prototypes */
void Init();

void Terminate();

/* Definitions */
int CALLBACK WinMain(HINSTANCE instance, HINSTANCE previous_instance, LPSTR args, int show_command)
{
	App::Init = Init;
	App::Terminate = Terminate;
	return App::Main();
}

void Init()
{
}

void Terminate()
{
}