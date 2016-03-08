#pragma once

class Sys {
public:
	virtual void Shutdown()			= 0;

	virtual void SendKeyEvents()	= 0;
};