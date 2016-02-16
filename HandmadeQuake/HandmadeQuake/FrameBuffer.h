#pragma once
#include "quakedef.h"

struct Color;

struct RGB8 {
	RGB8( uint8 Id = 0 ) : Id( Id ) {
	}

	uint8 Id;
};

struct RGB32 {
	RGB32( uint8 R = 0, uint8 G = 0, uint8 B = 0 ) : Red( R ), Green( G ), Blue( B ) {
	}

	uint8 Blue;
	uint8 Green;
	uint8 Red;

	operator uint32() {
		return (Red << 16) | (Green << 8) | (Blue);
	}

private:
	uint8 Reserved;
};

struct Color {
	Color( uint32& Data ) : Data( Data ) {
	}

	Color( uint8& Data ) : Data( Data ) {
	}

	Color( RGB8& Rgb ) : Data( Rgb.Id ) {
	}

	Color( RGB32& Rgb ) : Data( Rgb ) {
	}

	uint32 Data;

	//operator RGB32() {
	//	return RGB32( Data >> 16, Data >> 8, Data );
	//}
	//operator RGB8() {
	//	return (RGB8)Data;
	//}
};

class FrameBuffer {
public:
	FrameBuffer( uint32 Width, uint32 Height, uint32 BytesPerPixel );

	void SetPixel( uint32 X, uint32 Y, Color Color );

	const Color& GetPixel( uint32 X, uint32 Y ) const;

	void Clear( Color Color );

	operator void*();

	~FrameBuffer();

	const uint32 Width;
	const uint32 Height;
	const uint32 BytesPerPixel;

private:
	void* Buffer;

};

