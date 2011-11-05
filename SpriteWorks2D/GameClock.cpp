#include "stdafx.h"

LONGLONG cacheTime;

Timers::GameClock* Timers::GameClock::pInstance = NULL;

Timers::GameClock* Timers::GameClock::GetInstance ( ) { 
    if (pInstance == NULL) { 
        pInstance = new GameClock();
    }
    return pInstance;
}


Timers::GameClock::GameClock(void) {
    this->Initialize ( );
}

void Timers::GameClock::GetTime ( LONGLONG * t ) { 
    // Use timeGetTime() if queryperformancecounter is not supported 
    if (!QueryPerformanceCounter( (LARGE_INTEGER *) t)) { 
        *t = timeGetTime();
    }

    cacheTime = *t;
}

LONGLONG Timers::GameClock::GetTimeElapsed ( void ) { 
    LONGLONG t; 
    
    // Use timeGetTime() if queryperformancecounter is not supported
    if (!QueryPerformanceCounter( (LARGE_INTEGER *) &t )) { 
        t = timeGetTime();
    }

    return (t - cacheTime);
}

void Timers::GameClock::Initialize ( void ) { 
    if ( !QueryPerformanceFrequency((LARGE_INTEGER *) &this->frequency) ) { 
		this->frequency = 1000; // 1000ms to one second 
	}
    this->timeCount = DWORD(this->frequency / TICKS_PER_SECOND);
}

Timers::GameClock::~GameClock(void)
{
}
