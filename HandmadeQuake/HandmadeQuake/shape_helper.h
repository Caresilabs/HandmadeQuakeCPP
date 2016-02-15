#pragma once

#include "quakedef.h"
#include "screen_buffer.h"

void DrawCircle(ScreenBuffer& buffer, RGB_DATA color, int x, int y, int radius) {
	for ( int y = -radius; y <= radius; y++ )
		for ( int x = -radius; x <= radius; x++ )
			if ( x*x + y*y <= radius*radius )
				buffer.SetPixel( 320 + x, 240 + y , color);
}
