#include "sys_win.h"

LRESULT CALLBACK WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
	LRESULT Result = 0;

	switch ( uMsg ) {
	case WM_DESTROY:
		IsRunning = false;
		break;
	case WM_CREATE:
		break;
	case WM_KEYUP:
		IsRunning = false;
		break;
	default:
		Result = DefWindowProc( hWnd, uMsg, wParam, lParam );
		break;
	}
	return Result;
}

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd ) {

	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof( wc );
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = "Module 3";

	RegisterClassExA( &wc );

	DWORD dwExStyle = 0;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;

	bool Fullscreen = true;

	if ( Fullscreen ) {
		DEVMODE dmScreenSettings = { 0 };
		dmScreenSettings.dmSize = sizeof( dmScreenSettings );
		dmScreenSettings.dmPelsWidth = BufferWidth;
		dmScreenSettings.dmPelsHeight = BufferHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if ( ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN ) == DISP_CHANGE_SUCCESSFUL ) {
			dwExStyle = WS_EX_APPWINDOW;
			dwStyle = WS_POPUP;
		} else {
			Fullscreen = false;
		}
	}

	RECT WinRect = { 0 };
	WinRect.right = BufferWidth;
	WinRect.bottom = BufferHeight;
	AdjustWindowRectEx( &WinRect, dwStyle, 0, dwExStyle );


	HWND MainWindow = CreateWindowEx(
		dwExStyle, "Module 3", "Lesson 3.2", dwStyle,
		CW_USEDEFAULT, CW_USEDEFAULT,
		WinRect.right - WinRect.left, WinRect.bottom - WinRect.top,
		nullptr, nullptr,
		hInstance, 0 );

	if ( Fullscreen ) {
		SetWindowLong( MainWindow, GWL_STYLE, 0 );
	}

	ShowWindow( MainWindow, nShowCmd );

	// Define bitmap info
	BitMapInfo.bmiHeader.biSize = sizeof( BitMapInfo.bmiHeader );
	BitMapInfo.bmiHeader.biWidth = BufferWidth;
	BitMapInfo.bmiHeader.biHeight = BufferHeight;
	BitMapInfo.bmiHeader.biPlanes = 1;
	BitMapInfo.bmiHeader.biBitCount = 32;
	BitMapInfo.bmiHeader.biCompression = BI_RGB;

	BackBuffer = new uint32[BufferWidth * BufferHeight];

	MSG Message;
	while ( IsRunning ) {

		while ( PeekMessage( &Message, 0, 0, 0, PM_REMOVE ) ) {
			TranslateMessage( &Message );
			DispatchMessage( &Message );
		}

		RGB_DATA* MemoryWalker = (RGB_DATA*)BackBuffer;
		for ( int i = 0; i < BufferHeight; i++ ) {
			for ( int i = 0; i < BufferWidth; i++ ) {

				MemoryWalker->Red = 255;
				MemoryWalker->Green = 0;
				MemoryWalker->Blue = 0;

				++MemoryWalker;
				//(*MemoryWalker)->RGB = (Red << 16) | (Green << 8) | (Blue);
			}
		}

		HDC dc = GetDC( MainWindow );
		StretchDIBits( dc,
			0, 0, BufferWidth, BufferHeight,
			0, 0, BufferWidth, BufferHeight,
			BackBuffer, &BitMapInfo,
			DIB_RGB_COLORS, SRCCOPY
			);

		DeleteDC( dc );

	}

	SAFE_DELETE( BackBuffer );

	return EXIT_SUCCESS;
}