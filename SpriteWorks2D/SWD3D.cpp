#include "StdAfx.h"
#include "SWD3D.h"

namespace d3d { 
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
}
Renderers::D3DRend::D3DRend ( void ) { }

void Renderers::D3DRend::Render ( void ) { 
	// 
}

bool Renderers::D3DRend::StartupInterface ( HWND hWnd, int windowWidth, int windowHeight ) { 
	// Create the clear the DXGI_SWAP_CHAIN_DESC structure
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	
	// Fill in the needed values
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = windowWidth;
	swapChainDesc.BufferDesc.Height = windowHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	// Create the D3D device and the swap chain
	HRESULT hr = D3D10CreateDeviceAndSwapChain(NULL,
							D3D10_DRIVER_TYPE_HARDWARE, // IF this is anything other than hardware, GAME WILL SUCK
							NULL,
							0,
							D3D10_SDK_VERSION,
							&swapChainDesc,
							&d3d::pSwapChain,
							&d3d::pD3DDevice);

	// Ensure the device was created
	if (hr != S_OK) {
		MessageBox(hWnd, TEXT("A DX10 Compliant Video Card is Required"), TEXT("ERROR"), MB_OK);
		return false;
	}

	// Get the back buffer from the swapchain
	ID3D10Texture2D *pBackBuffer;
	hr = d3d::pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*) &pBackBuffer);
	if (hr != S_OK) {
		return false;
	}
	// Create the render target view
	hr = d3d::pD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &d3d::pRenderTargetView);

	// Release the back buffer
	pBackBuffer->Release();

	// Make sure the render target view was created successfully
	if (hr != S_OK) {
		return false;
	}

	 // Set the render target
	d3d::pD3DDevice->OMSetRenderTargets(1, &d3d::pRenderTargetView, NULL);

	// Create and set the viewport
	d3d::viewPort.Width = windowWidth;
	d3d::viewPort.Height = windowHeight;
	d3d::viewPort.MinDepth = 0.0f;
	d3d::viewPort.MaxDepth = 1.0f;
	d3d::viewPort.TopLeftX = 0;
	d3d::viewPort.TopLeftY = 0;

	d3d::pD3DDevice->RSSetViewports(1, &d3d::viewPort);
	
	D3DXMatrixOrthoOffCenterLH(&d3d::matProjection, 
		(float)d3d::viewPort.TopLeftX, 
		(float)d3d::viewPort.Width, 
		(float)d3d::viewPort.TopLeftY, 
		(float)d3d::viewPort.Height, 
		0.1f, 
		10);

	return true;
} // InitDirect3D

/**************************************
*** Shuts down the Direct3D Interface
***
***************************************/
void Renderers::D3DRend::ShutdownInterface ( void ) {
	// Release the original blend state object
	if (d3d::pOriginalBlendState10 != NULL){
		d3d::pOriginalBlendState10->Release();
		d3d::pOriginalBlendState10 = NULL;
	}

	// Release the blend state object
	if (d3d::pBlendState10 != NULL)	{
		d3d::pBlendState10->Release();
		d3d::pBlendState10 = NULL;
	}

    // release the ID3DX10Sprite object
    if (d3d::pSpriteObject)    {
        d3d::pSpriteObject->Release();
        d3d::pSpriteObject = NULL;
    }

	// Release the game font
	if (d3d::pGameFont) { 
		d3d::pGameFont->Release();
		d3d::pGameFont = NULL;
	}

	// release the rendertarget
	if (d3d::pRenderTargetView) 	{
		d3d::pRenderTargetView->Release();
	}

	// release the swapchain
    if (d3d::pSwapChain)	{
		d3d::pSwapChain->Release();
	}

	// release the D3D Device
    if (d3d::pD3DDevice)	{
		d3d::pD3DDevice->Release();
	}
} // ShutdownDirect3D

void Renderers::D3DRend::InitiateDefaultBlend(D3D10_BLEND_DESC* StateDesc) {
	ZeroMemory(StateDesc, sizeof(D3D10_BLEND_DESC));
	StateDesc->AlphaToCoverageEnable = FALSE;
	StateDesc->BlendEnable[0] = TRUE;	// If this is false, DUH we can't blend
	StateDesc->SrcBlend = D3D10_BLEND_SRC_ALPHA;
	StateDesc->DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
	StateDesc->BlendOp = D3D10_BLEND_OP_ADD;
	StateDesc->SrcBlendAlpha = D3D10_BLEND_ZERO;
	StateDesc->DestBlendAlpha = D3D10_BLEND_ZERO;
	StateDesc->BlendOpAlpha = D3D10_BLEND_OP_ADD;
	StateDesc->RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;
} // Initiate Default Blend


ID3D10Device* Renderers::D3DRend::GetDevice ( void ) { 
	return d3d::pD3DDevice;
}