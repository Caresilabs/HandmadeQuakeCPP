#pragma once

#include "Quakedef.h"

class Common {
public:
	#define MAX_NUM_ARGVS 50

	Common() =	default;

	void		ParseCmdLine( char* lpCmdLine );
	int32		CheckParm( char* Parm );

private:
	int32		ComArgc;
	char*		ComArgv[MAX_NUM_ARGVS + 1];
};

