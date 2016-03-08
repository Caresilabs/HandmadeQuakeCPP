#include "Quakedef.h"
#include "WinQuake.h"
#include "ShapeHelper.h"
#include "SysWin.h"

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd ) {
	SysWin Main;
	return Main.SysMain( hInstance, hPrevInstance, lpCmdLine, nShowCmd );
}

bool SysWin::IsRunning = true;
HINSTANCE GlobalInstance;

SysWin::SysWin() : MyHost(*this) {

}

//LRESULT SysWin::WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
//	LRESULT Result = 0;
//
//	switch ( uMsg ) {
//	case WM_DESTROY:
//		IsRunning = false;
//		break;
//	case WM_CREATE:
//		break;
//	case WM_KEYUP:
//		IsRunning = false;
//		break;
//	default:
//		Result = DefWindowProc( hWnd, uMsg, wParam, lParam );
//		break;
//	}
//	return Result;
//}

int SysWin::SysMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd ) {
	GlobalInstance = hInstance;

	Common Common;
	Common.ParseCmdLine( lpCmdLine );

	MyHost.Init();

	float Oldtime = InitFloatTime();

	while ( IsRunning ) {

		float NewTime = FloatTime();
		MyHost.Frame( NewTime - Oldtime );
		Oldtime = NewTime;

		//// Clear Screen
		//if ( BytesPerPixel == 1 ) {
		//	BackBuffer.Clear( RGB8() );
		//	DrawCircle( BackBuffer, RGB8( 2 ), 320, 240, 200, 20 );
		//} else {
		//	BackBuffer.Clear( RGB32( 255, 0, 0 ) );
		//	DrawRect( BackBuffer, RGB32( 0, 255, 0 ), 10, 10, 400, 200 );
		//}



	}

	MyHost.Shutdown();

	return EXIT_SUCCESS;
}

//////////////////////////////
//      TIMER CODE
//////////////////////////////

float SysWin::InitFloatTime() {
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency( &Frequency );

	SecondsPerTick = 1.0 / (double)Frequency.QuadPart;

	LARGE_INTEGER Counter;
	QueryPerformanceCounter( &Counter );

	GTimeCount = Counter.QuadPart;

	return 0;
}

float SysWin::FloatTime() {
	LARGE_INTEGER Counter;
	QueryPerformanceCounter( &Counter );

	__int64 Interval = Counter.QuadPart - GTimeCount;
	GTimeCount = Counter.QuadPart;

	double SecondsGoneBy = (double)Interval * SecondsPerTick;
	GTimePassed += SecondsGoneBy;

	return (float)GTimePassed;
}

//////////////////////////////
//      END TIMER CODE
//////////////////////////////

void SysWin::SendKeyEvents() {
	MSG Msg;
	// Check in with OS
	while ( PeekMessage( &Msg, NULL, 0, 0, PM_REMOVE ) ) {
		TranslateMessage( &Msg );
		DispatchMessage( &Msg );
	}
}

void SysWin::Shutdown() {
	IsRunning = false;
}
