#include "screen_buffer.h"


ScreenBuffer::ScreenBuffer( int width, int height ) : Width( width ), Height( height ) {
	Buffer = new uint32[Width * Height];
}

void ScreenBuffer::SetPixel( int x, int y, RGB_DATA color ) {
	*GetPixel( x, y ) = color;
}

RGB_DATA* ScreenBuffer::GetPixel( int x, int y ) {
	return  ((RGB_DATA*)Buffer) + (Width * y + x);
}

void ScreenBuffer::Clear( RGB_DATA color ) {
	RGB_DATA* MemoryWalker = (RGB_DATA*)Buffer;
	for ( int i = 0; i < Height; i++ ) {
		for ( int i = 0; i < Width; i++ ) {

			/*
			MemoryWalker->Red = 0;
			MemoryWalker->Green = 0;
			MemoryWalker->Blue = 0;
			*/

			*MemoryWalker = color;

			++MemoryWalker;
			//(*MemoryWalker)->RGB = (Red << 16) | (Green << 8) | (Blue);
		}
	}
}

ScreenBuffer::~ScreenBuffer() {
	SAFE_DELETE( Buffer );
}
