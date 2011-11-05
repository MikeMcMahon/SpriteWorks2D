#pragma once

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
}

namespace TextureUtils { 

    class TextureHandler { 
    public:
        static ID3D10Texture2D* GetTexture2DFromFile(LPCWSTR, ID3D10Device*);
        static void GetResourceViewFromTexture(ID3D10Texture2D*, ID3D10ShaderResourceView**, ID3D10Device*);

    }; // TextureHandler
} // GameUtil