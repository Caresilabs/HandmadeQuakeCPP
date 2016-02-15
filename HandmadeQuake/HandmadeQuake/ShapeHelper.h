#pragma once

#include "Quakedef.h"
#include "FrameBuffer.h"

void DrawCircle( FrameBuffer& Buffer, Color Color, uint32 X, uint32 Y, int Radius ) {
	for ( int y = -Radius; y <= Radius; y++ )
		for ( int x = -Radius; x <= Radius; x++ )
			if ( x*x + y*y <= Radius*Radius )
				Buffer.SetPixel( 320 + x, 240 + y, Color );
}

void DrawRect( FrameBuffer& Buffer, Color Color, uint32 X, uint32 Y, uint32 Width, uint32 Height ) {
	if ( X + Width > Buffer.Width )
		Width = Buffer.Width - X;

	if ( Y + Height > Buffer.Height - 1 )
		Height = Buffer.Height - Y - 1;

	for ( int yy = Y; yy < Y + Height; yy++ ) {
		for ( int xx = X; xx < X + Width; xx++ ) {
			Buffer.SetPixel( xx, yy, Color );
		}
	}
}
