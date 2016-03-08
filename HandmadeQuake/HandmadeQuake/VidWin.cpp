#include "WinQuake.h"
#include "Vid.h"
#include "Host.h"
#include "Sys.h"

#include "ShapeHelper.h"

static HWND				MainWindow;
static Vid*				GlobalVideo;
static BITMAPINFO		BitMapInfo = { 0 };

Vid::Vid( Host& MyHost ) : BackBuffer( BufferWidth, BufferHeight, BytesPerPixel ), MyHost( MyHost ) {
	GlobalVideo = this;
}


LRESULT CALLBACK Vid::MainWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
	LRESULT Result = 0;

	// catch any relevant messages here
	switch ( uMsg ) {
	case WM_ACTIVATE:

		break;

	case WM_CREATE:

		break;

	case WM_DESTROY:
		//Sys_Shutdown();
		break;

	case WM_KEYDOWN:
	{
		if ( wParam == 'A' ) {
			GlobalVideo->SetMode( 0 );
		} else if ( wParam == 'S' ) {
			GlobalVideo->SetMode( 1 );
		} else if ( wParam == 'D' ) {
			GlobalVideo->SetMode( 2 );
		} else if ( wParam == 'F' ) {
			GlobalVideo->SetMode( 3 );
		} else if ( wParam == '1' ) {
			GlobalVideo->SetMode( GlobalVideo->FirstFullscreenMode );
		} else if ( wParam == '2' ) {
			GlobalVideo->SetMode( GlobalVideo->FirstFullscreenMode + 1 );
		} else if ( wParam == 'Q' ) {
			GlobalVideo->MyHost.GetSystem().Shutdown();
		}

	} break;

	default:
		Result = DefWindowProc( hWnd, uMsg, wParam, lParam );
	}

	return Result;
}


void Vid::Init() {
	WNDCLASSEX Wc = { 0 };
	Wc.cbSize = sizeof( Wc );
	Wc.lpfnWndProc = Vid::MainWndProc;
	Wc.hInstance = GlobalInstance;
	Wc.hCursor = LoadCursor( nullptr, IDC_ARROW );
	Wc.lpszClassName = "Handmade Quake";

	if ( !RegisterClassEx( &Wc ) )
		exit( EXIT_FAILURE );

	InitWindowedMode();
	InitFullscreenMode();

	SetMode( 0 );
}

void Vid::Update() {
		BackBuffer.Clear( RGB32( 255, 0, 0 ) );
		DrawRect( BackBuffer, RGB32( 0, 255, 0 ), 10, 10, 400, 200 );

	// Draw buffer to the screen
	HDC DC = GetDC( MainWindow );
	StretchDIBits( DC,
		0, 0, BufferWidth, BufferHeight,
		0, 0, BufferWidth, BufferHeight,
		BackBuffer, (BITMAPINFO*)&BitMapInfo,
		DIB_RGB_COLORS, SRCCOPY
		);
	ReleaseDC( MainWindow, DC );
}

void Vid::Shutdown() {
	ChangeDisplaySettings( nullptr, 0 );
	DestroyWindow( MainWindow );
	//free( BackBuffer );
	//BackBuffer = NULL;
}

void Vid::InitWindowedMode() {
	ModeList[ModeCount].Type = ModeState::WINDOWED;
	ModeList[ModeCount].Width = 320;
	ModeList[ModeCount].Height = 240;
	ModeList[ModeCount].Hz = 0;
	ModeCount++;

	ModeList[ModeCount].Type = ModeState::WINDOWED;
	ModeList[ModeCount].Width = 640;
	ModeList[ModeCount].Height = 480;
	ModeList[ModeCount].Hz = 0;
	ModeCount++;

	ModeList[ModeCount].Type = ModeState::WINDOWED;
	ModeList[ModeCount].Width = 800;
	ModeList[ModeCount].Height = 600;
	ModeList[ModeCount].Hz = 0;
	ModeCount++;

	ModeList[ModeCount].Type = ModeState::WINDOWED;
	ModeList[ModeCount].Width = 1024;
	ModeList[ModeCount].Height = 768;
	ModeList[ModeCount].Hz = 0;
	ModeCount++;
}

void Vid::InitFullscreenMode() {
	DEVMODE DevMode;
	BOOL Success;
	int ModeNum = 0;
	int OldWidth = 0, OldHeight = 0;

	FirstFullscreenMode = ModeCount;

	do {
		Success = EnumDisplaySettings( NULL, ModeNum, &DevMode );

		if ( DevMode.dmPelsHeight == OldHeight && DevMode.dmPelsWidth == OldWidth ) {
			if ( DevMode.dmDisplayFrequency > ModeList[ModeCount - 1].Hz ) {
				ModeList[ModeCount - 1].Hz = DevMode.dmDisplayFrequency;
			}
			ModeNum++;
		} else {
			ModeList[ModeCount].Type = ModeState::FULLSCREEN;
			ModeList[ModeCount].Width = DevMode.dmPelsWidth;
			ModeList[ModeCount].Height = DevMode.dmPelsHeight;
			ModeList[ModeCount].Hz = DevMode.dmDisplayFrequency;
			ModeCount++;

			OldHeight = DevMode.dmPelsHeight;
			OldWidth = DevMode.dmPelsWidth;
			ModeNum++;
		}

	} while ( Success );
}

void Vid::SetWindowedMode( int ModeValue ) {
	DWORD WindowExStyle = 0;
	DWORD WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	// create rectangle for window
	RECT r = { 0 };
	r.right = WindowWidth;
	r.bottom = WindowHeight;
	AdjustWindowRectEx( &r, WindowStyle, 0, WindowExStyle );

	// create our window
	MainWindow = CreateWindowEx(
		WindowExStyle, "Handmade Quake",
		"Lesson 3.6", WindowStyle,
		CW_USEDEFAULT, CW_USEDEFAULT,
		r.right - r.left, r.bottom - r.top,
		NULL, NULL,
		GlobalInstance, 0 );
}

void Vid::SetFullscrenMode( int ModeValue ) {
	DWORD WindowExStyle = 0;
	DWORD WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	BOOL Fullscreen = TRUE;

	if ( Fullscreen ) {
		DEVMODE dmScreenSettings = { 0 };
		dmScreenSettings.dmSize = sizeof( dmScreenSettings );
		dmScreenSettings.dmPelsWidth = ModeList[ModeValue].Width;
		dmScreenSettings.dmPelsHeight = ModeList[ModeValue].Height;
		dmScreenSettings.dmDisplayFrequency = ModeList[ModeValue].Hz;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if ( ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN ) == DISP_CHANGE_SUCCESSFUL ) {
			WindowExStyle = WS_EX_APPWINDOW;
			WindowStyle = WS_POPUP;
		} else {
			Fullscreen = FALSE;
		}
	}

	// create rectangle for window
	RECT r = { 0 };
	r.right = WindowWidth;
	r.bottom = WindowHeight;
	AdjustWindowRectEx( &r, WindowStyle, 0, WindowExStyle );

	// create our window
	MainWindow = CreateWindowEx(
		WindowExStyle, "Handmade Quake",
		"Lesson 3.6", WindowStyle,
		CW_USEDEFAULT, CW_USEDEFAULT,
		r.right - r.left, r.bottom - r.top,
		NULL, NULL,
		GlobalInstance, 0 );

	SetWindowLong( MainWindow, GWL_STYLE, 0 );
}

void Vid::SetMode( int ModeValue ) {
	if ( BackBuffer ) {
		Shutdown();
	}

	WindowWidth = ModeList[ModeValue].Width;
	WindowHeight = ModeList[ModeValue].Height;

	BufferHeight = WindowHeight;
	BufferWidth = WindowWidth;

	if ( ModeList[ModeValue].Type == ModeState::WINDOWED ) {
		SetWindowedMode( ModeValue );
	} else {
		SetFullscrenMode( ModeValue );
	}

	ShowWindow( MainWindow, SW_SHOWDEFAULT );

	HDC DeviceContext = GetDC( MainWindow );
	PatBlt( DeviceContext, 0, 0, BufferWidth, BufferHeight, BLACKNESS );
	ReleaseDC( MainWindow, DeviceContext );

	// define our bitmap info
	BitMapInfo.bmiHeader.biSize = sizeof( BitMapInfo.bmiHeader );
	BitMapInfo.bmiHeader.biWidth = BufferWidth;
	BitMapInfo.bmiHeader.biHeight = -BufferHeight;
	BitMapInfo.bmiHeader.biPlanes = 1;
	BitMapInfo.bmiHeader.biBitCount = 8 * BytesPerPixel;
	BitMapInfo.bmiHeader.biCompression = BI_RGB;

	BackBuffer = FrameBuffer( BufferWidth, BufferHeight, BytesPerPixel );
}
