#include "FrameBuffer.h"


FrameBuffer::FrameBuffer( uint32 Width, uint32 Height, uint32 BytesPerPixel ) : Width( Width ), Height( Height ), BytesPerPixel( BytesPerPixel ) {
	if ( BytesPerPixel == 1 ) {
		Buffer = new uint8[Width * Height];
	} else {
		Buffer = new uint32[Width * Height];
	}
}

void FrameBuffer::SetPixel( uint32 X, uint32 Y, Color Color ) {
	if ( BytesPerPixel == 1 ) {
		*(((RGB8*)Buffer) + (Width * Y + X)) = Color;
	} else {
		*(((RGB32*)Buffer) + (Width * Y + X)) = Color;
	}
}

const Color& FrameBuffer::GetPixel( uint32 X, uint32 Y ) const {
	if ( BytesPerPixel == 1 ) {
		return  *((RGB8*)Buffer + (Width * Y + X));
	} else {
		return  *((RGB32*)Buffer + (Width * Y + X));
	}
}

void FrameBuffer::Clear( Color Color ) {
	if ( BytesPerPixel == 1 ) {
		RGB8* MemoryWalker = (RGB8*)Buffer;
		for ( int i = 0; i < Height; i++ ) {
			for ( int i = 0; i < Width; i++ ) {

				/*
				MemoryWalker->Red = 0;
				MemoryWalker->Green = 0;
				MemoryWalker->Blue = 0;
				*/

				*MemoryWalker = Color;
				++MemoryWalker;
				//(*MemoryWalker)->RGB = (Red << 16) | (Green << 8) | (Blue);
			}
		}
	} else {
		RGB32* MemoryWalker = (RGB32*)Buffer;
		for ( int i = 0; i < Height; i++ ) {
			for ( int i = 0; i < Width; i++ ) {
				*MemoryWalker = Color;
				++MemoryWalker;
			}
		}
	}
}

FrameBuffer::~FrameBuffer() {
	SAFE_DELETE( Buffer );
}
