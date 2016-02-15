#pragma once

#include "quakedef.h"
#include <windows.h>

union RGB_DATA {
	struct {
		uint8 Blue;
		uint8 Green;
		uint8 Red;
	};

	uint32 Data;
};

class sys_win {
public:
	sys_win() = default;

	static LRESULT CALLBACK WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	int SysMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd );

	~sys_win();
private:
	BITMAPINFO BitMapInfo = { 0 };
	const int BufferWidth = 640;
	const int BufferHeight = 480;
	void* BackBuffer;

	static bool IsRunning;
};


int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd );
