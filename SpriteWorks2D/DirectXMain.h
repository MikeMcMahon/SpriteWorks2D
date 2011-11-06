#pragma once

namespace DX {
	bool InitDirect3D(HWND hWnd, int windowWidth, int windowHeight);
	void ShutdownDirect3D ( void );

	void InitiateDefaultBlend ( D3D10_BLEND_DESC * );
	
	ID3D10Device* GetDevice ( void );
}