#pragma once

#include "Quakedef.h"
#include "Sys.h"
#include "Host.h"


//typedef struct dibinfo_s {
//	BITMAPINFOHEADER	bmiHeader;
//	RGBQUAD				acolor[256];
//} dibinfo_t;
//

class SysWin : public Sys {
public:
	SysWin();

	int				SysMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd );

	virtual void	Shutdown() override;

	virtual void	SendKeyEvents() override;

private:
	float			InitFloatTime();

	float			FloatTime();

	Host			MyHost;

	// TODO
	double			GTimePassed;
	double			SecondsPerTick;
	__int64			GTimeCount;

	static bool		IsRunning;
};


int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd );
