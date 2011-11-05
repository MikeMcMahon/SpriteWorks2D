#pragma once

/// NOTE ///////////////////////////////////////////////
/// The render engine must be set in here and then
/// recompiled for the specific engine the users wishes 
/// to use
////////////////////////////////////////////////////////
#define RENDER_ENG_DX // Render for the DX System
// #define RENDER_ENG_GL // not supported yet 

#include "SWColor.h"

namespace Timers { 
    class GameClock
    {
    public:
        static GameClock* GetInstance();
        void Initialize ( void );
        DWORD timeCount;

        void GetTime ( LONGLONG* t );
        LONGLONG GetTimeElapsed ( void );
        LONGLONG frequency; 

        ~GameClock(void);
    protected:
        GameClock(void);

    private:
        static GameClock* pInstance;
    }; // GameClock
} // Timers

namespace TextureUtils { 

    class TextureHandler { 
    public:
        static ID3D10Texture2D* GetTexture2DFromFile(LPCWSTR, ID3D10Device*);
        static void GetResourceViewFromTexture(ID3D10Texture2D*, ID3D10ShaderResourceView**, ID3D10Device*);

    }; // TextureHandler
} // TextureUtils

namespace Font {
	enum FontSize { 
		Tiny = 10,
		Normal = 20,
		Large = 30,
		Huge = 40
	};

	class FontHandler { 
	public: 
		bool InitFont();
		void DrawTextNow(float x, float y, LPCWSTR text, Util::SWColor color = SW_BLACK);
		void FontRect(RECT* rect, float x, float y);
	};
} // Font
