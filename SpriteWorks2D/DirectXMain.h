#pragma once

namespace DX {
	// D3D GLOBALS ////////////////////////////////
	ID3D10Device* pD3DDevice = NULL;
	IDXGISwapChain* pSwapChain = NULL;
	ID3D10RenderTargetView* pRenderTargetView = NULL;
	D3DXMATRIX matProjection;
	D3D10_VIEWPORT viewPort;

	// Blend State
	ID3D10BlendState* pBlendState10 = NULL;
	ID3D10BlendState* pOriginalBlendState10 = NULL;
	ID3D10BlendState* pFontOriginalBlendState10 = NULL;

	// Shader Resource View
	ID3D10ShaderResourceView* gSpriteTextureRV = NULL;

	// Sprite stuff
	ID3DX10Sprite* pSpriteObject = NULL;
	D3DX10_SPRITE  spritePool[NUM_POOL_SPRITES];
	ID3DX10Font* pGameFont = NULL;

	bool InitDirect3D(HWND hWnd, int windowWidth, int windowHeight);
	void ShutdownDirect3D ( void );

	void InitiateDefaultBlend ( D3D10_BLEND_DESC * );
	
	ID3D10Device* GetDevice ( void );
}