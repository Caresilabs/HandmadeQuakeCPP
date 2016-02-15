#include "FrameBuffer.h"


FrameBuffer::FrameBuffer( int Width, int Height ) : Width( Width ), Height( Height ) {
	Buffer = new uint32[Width * Height];
}

void FrameBuffer::SetPixel( int X, int Y, RGB8 Color ) {
	*(((RGB8*)Buffer) + (Width * Y + X)) = Color;
}

const RGB8* FrameBuffer::GetPixel( int X, int Y ) const {
	return  ((RGB8*)Buffer) + (Width * Y + X);
}

void FrameBuffer::Clear( RGB8 color ) {
	RGB8* MemoryWalker = (RGB8*)Buffer;
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

FrameBuffer::~FrameBuffer() {
	SAFE_DELETE( Buffer );
}
