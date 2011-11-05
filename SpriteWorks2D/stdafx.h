// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// TODO: reference additional headers your program requires here

#define STRICT
// #define WINVER       0x500

#include <Windows.h>
#include <WindowsX.h>

#include <D3D10.h>
#include <D3DX10.h>
#include <XInput.h>

#include <tchar.h>
#include <vector>
#include <string>

#include <SpriteWorks2D.h>

// Required for rendering stuff on time
#ifndef TICKS_PER_SECOND
	#define TICKS_PER_SECOND 60
#endif

#define SKIP_TICKS (1000.0f / (float)TICKS_PER_SECOND)

#ifndef MAX_FRAMESKIP
	#define MAX_FRAMESKIP 5
#endif

// Sprite calcs
#ifndef MAX_SPRITES
	#define MAX_SPRITES			2048
#endif
#define NUM_POOL_SPRITES	MAX_SPRITES

// Window handling stuff
// TODO put these somewhere else, not in a define 
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

#ifndef CLASS_NAME
	#define CLASS_NAME TEXT("DarkSeed")
#endif

#if _DEBUG
    #define DIRECTORY_PREFIX "../"
#else 
    #define DIRECTORY_PREFIX "./"
#endif


/* eof */