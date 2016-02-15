#include "SysWin.h"
#include "ShapeHelper.h"

bool SysWin::IsRunning = true;

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd ) {
	SysWin main;
	return main.SysMain(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
}

SysWin::SysWin() : BackBuffer( BufferWidth, BufferHeight ) {
}

LRESULT SysWin::WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
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

int SysWin::SysMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd ) {
	WNDCLASSEX Wc = { 0 };
	Wc.cbSize = sizeof( Wc );
	Wc.lpfnWndProc = SysWin::WindowProc;
	Wc.hInstance = hInstance;
	Wc.lpszClassName = "Module 3";

	RegisterClassExA( &Wc );

	DWORD dwExStyle = 0;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;

	bool Fullscreen = false;

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
		dwExStyle, "Module 3", "Lesson 3.3", dwStyle,
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
	BitMapInfo.bmiHeader.biHeight = -BufferHeight;
	BitMapInfo.bmiHeader.biPlanes = 1;
	BitMapInfo.bmiHeader.biBitCount = 32;
	BitMapInfo.bmiHeader.biCompression = BI_RGB;

	MSG Message;
	while ( IsRunning ) {

		while ( PeekMessage( &Message, 0, 0, 0, PM_REMOVE ) ) {
			TranslateMessage( &Message );
			DispatchMessage( &Message );
		}

		// Clear Screen
		BackBuffer.Clear(RGB8(0, 0, 0));

		DrawRect(BackBuffer, 10, 10, 400, 200, RGB8(255, 0, 0));

		/*
		RGB_DATA* Ptr = ((RGB_DATA*)BackBuffer) + (BufferWidth * 1 + 1);
		for ( int t = 1; t < 110; t++ ) {

			for ( float i = 0; i < 3.14*2.f; i+= (t *  0.0001f) ) {

				Ptr->Red = 255;
				Ptr->Green = 0;
				Ptr->Blue = 0;

				Ptr = Get( 320 + cos( i ) * t, 240 + sin( i ) * t );
			}
		}*/

		HDC DC = GetDC( MainWindow );
		StretchDIBits( DC,
			0, 0, BufferWidth, BufferHeight,
			0, 0, BufferWidth, BufferHeight,
			BackBuffer, &BitMapInfo,
			DIB_RGB_COLORS, SRCCOPY
		);

		DeleteDC( DC );

	}

	DestroyWindow( MainWindow );

	return EXIT_SUCCESS;
}

SysWin::~SysWin() {
}
