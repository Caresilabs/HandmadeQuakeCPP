#pragma once

#include "quakedef.h"
#include "screen_buffer.h"
#include <windows.h>


class SysWin {
public:
	SysWin();

	static LRESULT CALLBACK WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	int SysMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd );

	~SysWin();
private:
	BITMAPINFO BitMapInfo = { 0 };
	const int BufferWidth = 640;
	const int BufferHeight = 480;
	
	ScreenBuffer BackBuffer;

	static bool IsRunning;
};


int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd );
