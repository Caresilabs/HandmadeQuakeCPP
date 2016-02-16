#pragma once

#include "quakedef.h"
#include "FrameBuffer.h"
#include <windows.h>

typedef struct dibinfo_s {
	BITMAPINFOHEADER	bmiHeader;
	RGBQUAD				acolor[256];
} dibinfo_t;


class SysWin {
public:
	SysWin();

	static LRESULT CALLBACK WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	int SysMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd );

	~SysWin();
private:
	static bool IsRunning;

	const int BufferWidth = 640;
	const int BufferHeight = 480;
	const int BytesPerPixel = 1;

	dibinfo_t BitMapInfo = { 0 };
	FrameBuffer BackBuffer;
	
};


int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd );
