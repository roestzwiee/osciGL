#pragma once
#include <chrono>
#include <iostream>
#include <thread>

#include "../Headers/IUserControls.h"
#include <windows.h>
#include <consoleapi.h>
#include <winbase.h>

using namespace std;

typedef chrono::high_resolution_clock Time;

class ConsoleView
{
public:

	ConsoleView(IUserControls* userControls)
	{
		this->userControls = userControls;
		lastUpdated = Time::now();


		HANDLE hInput = CreateFileW(L"CONIN$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);

		DWORD prev_mode;
		GetConsoleMode(hInput, &prev_mode);
		SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS );
		
	}

	void runMultiThread()
	{
		if (stayActive == false)
		{
			stayActive = true;
			consoleViewThread = std::thread(&ConsoleView::view, this);
		}
	}

	void stopMultiThread()
	{
		stayActive = false;
		consoleViewThread.join();
	}

	void view()
	{
		do
		{
			do
			{
				this_thread::sleep_for(chrono::milliseconds(50));
			}
			while (isDeBounceRequired());

			// Clear Console
			system("CLS");

			printBanner();
			printCameraPosition();
		}
		while (stayActive);
	}

	void printBanner() const
	{
		cout << BANNER << endl;
	}

	bool isDeBounceRequired()
	{
		const auto millis = chrono::duration_cast<chrono::milliseconds>(Time::now() - lastUpdated).count();
		const bool isRequired = millis <= 250;

		if (!isRequired)
		{
			lastUpdated = Time::now();
		}

		return isRequired;
	}

	void printCameraPosition() const
	{
		// TODO: make this more understandable, e.g. create a camera class

		char buffer[90];
		sprintf_s(buffer, "Camera Position: x: %2f, y: %2f, z: %2f", -userControls->getTranslationInX(),
		          -userControls->getTranslationInY(), -userControls->getTranslationInZ());

		cout << buffer << endl;
	}

private:
	IUserControls* userControls;
	std::chrono::high_resolution_clock::time_point lastUpdated;
	std::thread consoleViewThread;

	bool stayActive = false;

	const string BANNER =
		"       ____                    _    ______    __     \r\n"
		"      / __ \\   _____  _____   (_)  / ____/   / /    \r\n"
		"     / / / /  / ___/ / ___/  / /  / / __    / /      \r\n"
		"    / /_/ /  (__  ) / /__   / /  / /_/ /   / /___    \r\n"
		"    \\____/  /____/  \\___/  /_/   \\____/   /_____/ \r\n";
};


// snippets
//
// Querry window cols and rows:
// 
//		CONSOLE_SCREEN_BUFFER_INFO csbi;
//		int columns, rows;
//
//		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
//		columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
//		rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
