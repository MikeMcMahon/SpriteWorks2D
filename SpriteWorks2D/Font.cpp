#include "stdafx.h"

#ifdef RENDER_ENG_DX
		bool _dx_InitFont(ID3D10Device* device, ID3DX10Font** font, int height, UINT width, UINT fontWeight, LPCWSTR fontFace);
		void _dx_DrawTextNow(ID3DX10Font* pFont,ID3DX10Sprite* pSprite, float x, float y, LPCWSTR text, Util::SWColor color = SW_BLACK);
		void _dx_FontRect(ID3DX10Font* pFont,ID3DX10Sprite* pSprite, RECT* rect, float x, float y, LPCWSTR text);
#endif

bool Font::FontHandler::InitFont ( ) { 
#ifdef RENDER_ENG_DX
	return true;
#else 
	return false;
#endif
}

void Font::FontHandler::DrawTextNow(float x, float y, LPCWSTR text, Util::SWColor color) { 
#ifdef RENDER_ENG_DX
	return;
#else 
	return;
#endif
}

void Font::FontHandler::FontRect(RECT* rect, float x, float y) { 
#ifdef RENDER_ENG_DX
	return;
#else 
	return;
#endif
}

#ifdef RENDER_ENG_DX
bool _dx_InitFont(ID3D10Device* device, ID3DX10Font** font, int height, UINT width, UINT fontWeight, LPCWSTR fontFace) { 
	SW_BLACK = Util::SWColor(0.0f, 0.0f, 0.0f, 1.0f);

	HRESULT hr = D3DX10CreateFont(
		device,
		height, width,
		fontWeight,
		1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_TT_ONLY_PRECIS,
		NONANTIALIASED_QUALITY, 
		DEFAULT_PITCH || FF_DONTCARE,
		fontFace,
		font);
	if (FAILED(hr)) { 
		return false;
	}
	return true;
}

void _dx_DrawTextNow(ID3DX10Font* pFont,ID3DX10Sprite* pSprite, float x, float y, LPCWSTR text, Util::SWColor color) {
	RECT rc;
	SetRectEmpty(&rc);

	// Get the rectangle dimension
	pFont->DrawText(pSprite,text,-1,&rc,DT_CALCRECT,color);

	// Apply the x/y if there is one
	if (x > 0) { 
		rc.left += (LONG)x;
		rc.right += (LONG)x;
	}
	if (y > 0) { 
		rc.top += (LONG)y;
		rc.bottom += (LONG)y;
	}

	// Actually draw the text
	pFont->DrawText(pSprite, text, -1, &rc, 0, color);
}

void _dx_FontRect(ID3DX10Font* pFont,ID3DX10Sprite* pSprite, RECT* rect, float x, float y, LPCWSTR text) { 
	SetRectEmpty(rect);

	// Get the rectangle dimension
	pFont->DrawText(pSprite,text,-1,rect,DT_CALCRECT, SW_BLACK);

	// Apply the x/y if supplied
	if (x > 0) { 
		rect->left += (LONG)x;
		rect->right += (LONG)x;
	}
	if (y > 0) { 
		rect->top += (LONG)y;
		rect->bottom += (LONG)y;
	}
}
#endif

/* eof */