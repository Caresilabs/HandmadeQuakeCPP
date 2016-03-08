#include "Quakedef.h"
#include "WinQuake.h"
#include "SysWin.h"

bool			SysWin::IsRunning = true;
HINSTANCE		GlobalInstance;

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd ) {
	SysWin Main;
	return Main.SysMain( hInstance, hPrevInstance, lpCmdLine, nShowCmd );
}


SysWin::SysWin() : MyHost(*this), GTimeCount(0), GTimePassed(0), SecondsPerTick(0) {
}

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
