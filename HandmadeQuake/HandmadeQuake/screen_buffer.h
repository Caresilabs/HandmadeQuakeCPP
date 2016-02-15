#pragma once
#include "quakedef.h"

union RGB_DATA {
	RGB_DATA( int r = 0, int g = 0, int b = 0 ) : Red( r ), Green( g ), Blue( b ) {
	}

	struct {
		uint8 Blue;
		uint8 Green;
		uint8 Red;
	};

	uint32 Data;
};

class ScreenBuffer {
public:
	ScreenBuffer( int width, int height );

	void SetPixel( int x, int y, RGB_DATA color );

	RGB_DATA* GetPixel( int x, int y );

	void Clear( RGB_DATA color );

	operator void*() {
		return Buffer;
	}

	~ScreenBuffer();
private:
	void* Buffer;
	int Width;
	int Height;
};

