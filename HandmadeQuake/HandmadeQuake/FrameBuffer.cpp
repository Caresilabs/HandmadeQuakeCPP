#include "FrameBuffer.h"


FrameBuffer::FrameBuffer( uint32 Width, uint32 Height, uint32 BytesPerPixel ) : Width( Width ), Height( Height ), BytesPerPixel( BytesPerPixel ) {
	if ( BytesPerPixel == 1 ) {
		Buffer = new uint8[Width * Height];
	} else {
		Buffer = new uint32[Width * Height];
	}
}

FrameBuffer& FrameBuffer::operator=( FrameBuffer&& Rhs ) {
	delete Buffer;

	Width = Rhs.Width;
	Height = Rhs.Height;
	BytesPerPixel = Rhs.BytesPerPixel;

	// Cpy buffer
	Buffer = Rhs.Buffer;
	Rhs.Buffer = nullptr;

	return *this;
}

void FrameBuffer::SetPixel( uint32 X, uint32 Y, Color Color ) {
	if ( BytesPerPixel == 1 ) {
		*(((uint8*)Buffer) + (Width * Y + X)) = Color.Data;
	} else {
		*(((uint32*)Buffer) + (Width * Y + X)) = Color.Data;
	}
}

const Color& FrameBuffer::GetPixel( uint32 X, uint32 Y ) const {
	if ( BytesPerPixel == 1 ) {
		return  *((uint8*)Buffer + (Width * Y + X));
	} else {
		return  *((uint32*)Buffer + (Width * Y + X));
	}
}

void FrameBuffer::Clear( Color Color ) {
	if ( BytesPerPixel == 1 ) {
		uint8* MemoryWalker = (uint8*)Buffer;
		for ( int i = 0; i < Height; i++ ) {
			for ( int i = 0; i < Width; i++ ) {

				/*
				MemoryWalker->Red = 0;
				MemoryWalker->Green = 0;
				MemoryWalker->Blue = 0;
				*/

				*MemoryWalker = (uint8)Color.Data;
				++MemoryWalker;
				//(*MemoryWalker)->RGB = (Red << 16) | (Green << 8) | (Blue);
			}
		}
	} else {
		uint32* MemoryWalker = (uint32*)Buffer;
		for ( int i = 0; i < Height; i++ ) {
			for ( int i = 0; i < Width; i++ ) {
				*MemoryWalker = Color.Data;
				++MemoryWalker;
			}
		}
	}
}

FrameBuffer::operator void*() {
	return Buffer;
}

FrameBuffer::~FrameBuffer() {
	SAFE_DELETE_ARRAY( Buffer );
}
