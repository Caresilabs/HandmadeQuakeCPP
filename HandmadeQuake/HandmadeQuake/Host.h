#pragma once

#include "Vid.h"

class Sys;

class Host {
public:

			Host( Sys& System );

	void	Init();
	void	Frame( float Timestep );
	void	Shutdown();

	Sys&	GetSystem();

private:
	bool	FilterTime( float Time );

	double	Realtime;
	double	OldRealtime;
	double	HostFrametime;

	Sys&	System;
	Vid		Video;

};

