#include <windows.h>    // Win32API Header File
#include <conio.h>
#include <iostream>

#include "image2d.h"

static HWND GetConsoleWndHandle();
static void ShowConsoleCursor(bool showFlag);
static int PutPixel(int x, int y, COLORREF crColor, HWND hConWnd, HDC drawHDC = nullptr);


int DisplayImage(const ImageData& image)
{
	const int maxWidth = 960;
	const int maxHeight = 480;
	if (maxWidth < image.GetWidth() || maxHeight < image.GetHeight())
	{
		std::cout << "Can't print. Max size is " << maxHeight << " x " << maxWidth << std::endl;
		return 0;
	}
	// center image
	int leftTopCornerX = (maxWidth - image.GetWidth()) / 2;
	int leftTopCornerY = (maxHeight - image.GetHeight()) / 2;

	HWND hConWnd = GetConsoleWndHandle();
	if (!hConWnd)
	{
		return -1;
	}

	auto maxColor = 255;
	auto drawHdc = GetDC(hConWnd);
	for (int column = 0; column < image.GetColumns(); ++column)
	{
		for (int row = 0; row < image.GetRows(); ++row)
		{
			const auto& clr = image.Get(column, row);
			auto colorInt = ColorFloatToInt(clr, maxColor);
			const auto gdiColor RGB(colorInt.r, colorInt.g, colorInt.b);
			PutPixel(leftTopCornerX + column, leftTopCornerY + row, gdiColor, hConWnd, drawHdc);
		}
	}
	ReleaseDC(hConWnd, drawHdc);

	ShowConsoleCursor(false);
	// wait for input
	while (!_kbhit())
	{
		Sleep(50);
	}
	ShowConsoleCursor(true);
	
	return 0;
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

int PutPixel(int x, int y, COLORREF crColor, HWND hConWnd, HDC drawHDC)
{
	int createdDC = 0;
	if (!drawHDC)
	{
		drawHDC = GetDC(hConWnd);
		createdDC = 1;
	}
	int result = SetPixel(drawHDC, x, y, crColor);
	if (createdDC)
	{
		ReleaseDC(hConWnd, drawHDC);
	}
	return result;
}

HWND GetConsoleWndHandle()
{
	HWND hConWnd;
	WCHAR szOriginalTitle[1024];

	GetConsoleTitle(szOriginalTitle, sizeof(szOriginalTitle));
	const auto szTempTitle =  L"Raytracing_WeekendProject123";// GetTickCount(), GetCurrentProcessId());
	SetConsoleTitle(szTempTitle);
	Sleep(40);

	hConWnd = FindWindow(nullptr, szTempTitle);
	SetConsoleTitle(szOriginalTitle);

	return hConWnd;
}