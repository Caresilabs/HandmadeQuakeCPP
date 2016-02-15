#pragma once

#include "quakedef.h"
#include <windows.h>

union RGB_DATA {
	struct {
		uint8 Blue;
		uint8 Green;
		uint8 Red;
	};

	uint32 data;
};

bool IsRunning = true;

int BufferWidth = 640;
int BufferHeight = 480;
void* BackBuffer;

BITMAPINFO BitMapInfo = { 0 };


LRESULT CALLBACK WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd );
