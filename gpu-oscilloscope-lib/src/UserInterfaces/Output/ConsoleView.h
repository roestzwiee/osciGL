#pragma once

#include <chrono>
#include <iostream>
#include <thread>
#include "../../Headers/IUserControls.h"
#include <windows.h>
#include <consoleapi.h>
#include <winbase.h>
#include "IInfoOutput.h"

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
		cls();
		do
		{
			do
			{
				this_thread::sleep_for(chrono::milliseconds(100));
			}
			while (isDeBounceRequired());


			setCursorPosition(0, 0);
			printBanner();

			setCursorPosition(0, 7);
			printCameraPosition();

			currentCursorLine = 8;
			printInfoOutputs();
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
		const auto cameraPosition = userControls->getCameraPosition();
		
		char buffer[90];
		sprintf_s(buffer, "Camera Position: x: %2f, y: %2f, z: %2f", cameraPosition.x, cameraPosition.y, cameraPosition.z );

		cout << buffer << endl;
	}

	void printInfoOutputs()
	{
		for (IInfoOutput* infoOutput: infoOutputs)
		{
			++currentCursorLine;
			printInfoDataList(infoOutput->getInfoData());
		}
	}

	void printInfoDataList(list<InfoData> list)
	{
		for(InfoData infoData  : list)
		{
			setCursorPosition(0, ++currentCursorLine);
			cout << infoData.label << ": " << infoData.value;
		}
	}
	
	void addInfoOutput(IInfoOutput* infoOutput)
	{
		infoOutputs.push_back(infoOutput);
	}

private:
	IUserControls* userControls;
	std::chrono::high_resolution_clock::time_point lastUpdated;
	std::thread consoleViewThread;
	std::list<IInfoOutput*> infoOutputs;
	
	bool stayActive = false;

	int currentCursorLine;

	const string BANNER =
		"       ____                    _    ______    __     \r\n"
		"      / __ \\   _____  _____   (_)  / ____/   / /    \r\n"
		"     / / / /  / ___/ / ___/  / /  / / __    / /      \r\n"
		"    / /_/ /  (__  ) / /__   / /  / /_/ /   / /___    \r\n"
		"    \\____/  /____/  \\___/  /_/   \\____/   /_____/ \r\n";

	void cls()
	{
		// Get the Win32 handle representing standard output.
		// This generally only has to be done once, so we make it static.
		static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD topLeft = { 0, 0 };

		// std::cout uses a buffer to batch writes to the underlying console.
		// We need to flush that to the console because we're circumventing
		// std::cout entirely; after we clear the console, we don't want
		// stale buffered text to randomly be written out.
		std::cout.flush();

		// Figure out the current width and height of the console window
		if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
			// TODO: Handle failure!
			abort();
		}
		DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

		DWORD written;

		// Flood-fill the console with spaces to clear it
		FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

		// Reset the attributes of every character to the default.
		// This clears all background colour formatting, if any.
		FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

		// Move the cursor back to the top left for the next sequence of writes
		SetConsoleCursorPosition(hOut, topLeft);


		CONSOLE_CURSOR_INFO     cursorInfo;
		GetConsoleCursorInfo(hOut, &cursorInfo);
		cursorInfo.bVisible = false; // set the cursor visibility
		SetConsoleCursorInfo(hOut, &cursorInfo);
	}


	static void setCursorPosition(int x, int y)
	{
		// x is the column, y is the row. The origin (0,0) is top-left.
		static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		std::cout.flush();
		const COORD coord = { (SHORT)x, (SHORT)y };
		SetConsoleCursorPosition(hOut, coord);
	}
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
