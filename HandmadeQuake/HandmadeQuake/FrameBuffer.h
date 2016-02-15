#pragma once
#include "quakedef.h"

union RGB8 {
	RGB8( int R = 0, int G = 0, int B = 0 ) : Red( R ), Green( G ), Blue( B ) {
	}

	struct {
		uint8 Blue;
		uint8 Green;
		uint8 Red;
	};

	uint32 Data;
};

class FrameBuffer {
public:
	FrameBuffer( int Width, int Height );

	void SetPixel( int X, int Y, RGB8 Color );

	const RGB8* GetPixel( int X, int Y ) const;

	void Clear( RGB8 Color );

	operator void*() {
		return Buffer;
	}

	~FrameBuffer();

	const int Width;
	const int Height;

private:
	void* Buffer;

};

