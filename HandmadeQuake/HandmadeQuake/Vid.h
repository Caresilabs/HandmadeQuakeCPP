#pragma once


#include "FrameBuffer.h"
#include "Quakedef.h"

class Host;

enum class ModeState { 
	WINDOWED, FULLSCREEN 
};

struct VMode {
	ModeState	Type;
	int32		Width;
	int32		Height;
	uint32		Hz;
};

class Vid {
public:

				Vid( Host& MyHost );

	void		Init();
	void		Update();
	void		Shutdown();
	void		SetMode( int ModeValue );

	Host&		MyHost;
	int32		FirstFullscreenMode;

private:

	void		InitWindowedMode();
	void		InitFullscreenMode();

	void		SetWindowedMode( int ModeValue );
	void		SetFullscrenMode( int ModeValue );

	int			WindowWidth = 0;
	int			WindowHeight = 0;
	int			BufferWidth = 640;
	int			BufferHeight = 480;
	const int	BytesPerPixel = 4;

	FrameBuffer BackBuffer;

	VMode		ModeList[40];
	int32		ModeCount = 0;

};