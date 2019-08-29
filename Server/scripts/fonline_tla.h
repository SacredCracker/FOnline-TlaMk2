#ifndef __FONLINE_TLA__
#define __FONLINE_TLA__

// Script constants
#define SKIP_PRAGMAS
#include "_defines.fos"

// Disable macro redefinition warning
#pragma warning (push)
#pragma warning (disable : 4005)
#include "fonline.h"
#pragma warning (pop)

// Script global variables
struct _GlobalVars
{
	bool* __NewbieLocationIsActive;
    uint* __HitAimEyes;
    uint* __HitAimHead;
    uint* __HitAimGroin;
    uint* __HitAimTorso;
    uint* __HitAimArms;
    uint* __HitAimLegs;
	uint* __MaxLifeLevelSoftCap;
	uint* __EncounterTime;
	uint* __ExperienceRate;
    #ifdef __CLIENT
    bool* __AutoAim;
    bool* __GrenadeMode;
    #endif
	#ifdef __SERVER
	uint16* __StartServerVersion;
	#endif
} extern GlobalVars;

#include "windows.h"

#ifdef __SERVER
# pragma comment(lib, "shell32.lib")
#endif
#endif // __FONLINE_TLA__
