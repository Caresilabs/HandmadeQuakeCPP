#include "Quakedef.h"
#include "Host.h"
#include "Sys.h"

Host::Host( Sys& System ) : System( System ), Video( *this ), Realtime( 0 ), OldRealtime( 0 ), HostFrametime( 0 ) {
}

bool Host::FilterTime( float Time ) {
	Realtime += Time;

	if ( Realtime - OldRealtime < 1.0 / 72.0 )
		return false;

	HostFrametime = Realtime - OldRealtime;
	OldRealtime = Realtime;

	return true;
}


void Host::Init() {
	Video.Init();
}

void Host::Frame( float Timestep ) {
	if ( !FilterTime( Timestep ) )
		return;

	System.SendKeyEvents();

	Video.Update();
	// update game
	// render scene
}

void Host::Shutdown() {
	Video.Shutdown();
}

Sys& Host::GetSystem() {
	return System;
}
