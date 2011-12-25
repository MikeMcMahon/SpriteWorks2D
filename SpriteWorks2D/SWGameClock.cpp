#include "stdafx.h"

LONGLONG cacheTime;

Timers::SWGameClock* Timers::SWGameClock::pInstance = NULL;

Timers::SWGameClock* Timers::SWGameClock::GetInstance ( ) { 
    if (pInstance == NULL) { 
        pInstance = new SWGameClock();
    }
    return pInstance;
}


Timers::SWGameClock::SWGameClock(void) {
    this->Initialize ( );
}

void Timers::SWGameClock::GetTime ( LONGLONG * t ) { 
    // Use timeGetTime() if queryperformancecounter is not supported 
    if (!QueryPerformanceCounter( (LARGE_INTEGER *) t)) { 
        *t = timeGetTime();
    }

    cacheTime = *t;
}

LONGLONG Timers::SWGameClock::GetTimeElapsed ( void ) { 
    LONGLONG t; 
    
    // Use timeGetTime() if queryperformancecounter is not supported
    if (!QueryPerformanceCounter( (LARGE_INTEGER *) &t )) { 
        t = timeGetTime();
    }

    return (t - cacheTime);
}

void Timers::SWGameClock::Initialize ( void ) { 
    if ( !QueryPerformanceFrequency((LARGE_INTEGER *) &this->frequency) ) { 
		this->frequency = 1000; // 1000ms to one second 
	}
    this->timeCount = DWORD(this->frequency / TICKS_PER_SECOND);
}

Timers::SWGameClock::~SWGameClock(void)
{
}
