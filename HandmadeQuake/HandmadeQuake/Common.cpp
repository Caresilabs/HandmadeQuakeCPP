#include "Common.h"

void Common::ParseCmdLine( char* lpCmdLine ) {
	ComArgv[0] = "";

	while ( *lpCmdLine && (ComArgc < MAX_NUM_ARGVS + 1) ) {
		while ( *lpCmdLine && ((*lpCmdLine <= 32) || (*lpCmdLine > 126)) )
			lpCmdLine++;

		if ( *lpCmdLine ) {
			ComArgv[ComArgc] = lpCmdLine;
			ComArgc++;

			while ( *lpCmdLine && ((*lpCmdLine > 32) && (*lpCmdLine <= 126)) )
				lpCmdLine++;

			if ( *lpCmdLine ) {
				*lpCmdLine = 0;
				lpCmdLine++;
			}
		}
	}
}

int32 Common::CheckParm( char* Parm ) {
	for ( int32 i = 1; i < ComArgc; i++ ) {
		if ( !QStrcmp( Parm, ComArgv[i] ) )
			return i;
	}

	return 0;
}
