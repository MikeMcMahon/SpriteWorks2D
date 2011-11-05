#include "StdAfx.h"
#include "DirectXMain.h"

bool DX::InitDirect3D ( HWND hWnd, int windowWidth, int windowHeight ) { 
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
							&pSwapChain,
							&pD3DDevice);

	// Ensure the device was created
	if (hr != S_OK) {
		MessageBox(hWnd, TEXT("A DX10 Compliant Video Card is Required"), TEXT("ERROR"), MB_OK);
		return false;
	}

	// Get the back buffer from the swapchain
	ID3D10Texture2D *pBackBuffer;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*) &pBackBuffer);
	if (hr != S_OK) {
		return false;
	}
	// Create the render target view
	hr = pD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);

	// Release the back buffer
	pBackBuffer->Release();

	// Make sure the render target view was created successfully
	if (hr != S_OK) {
		return false;
	}

	 // Set the render target
	pD3DDevice->OMSetRenderTargets(1, &pRenderTargetView, NULL);

	// Create and set the viewport
	viewPort.Width = windowWidth;
	viewPort.Height = windowHeight;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;

	pD3DDevice->RSSetViewports(1, &viewPort);
	
	D3DXMatrixOrthoOffCenterLH(&matProjection, 
		(float)viewPort.TopLeftX, 
		(float)viewPort.Width, 
		(float)viewPort.TopLeftY, 
		(float)viewPort.Height, 
		0.1f, 
		10);

	return true;
} // InitDirect3D

/**************************************
*** Shuts down the Direct3D Interface
***
***************************************/
void DX::ShutdownDirect3D ( void ) {
	// Release the original blend state object
	if (pOriginalBlendState10 != NULL){
		pOriginalBlendState10->Release();
		pOriginalBlendState10 = NULL;
	}

	// Release the blend state object
	if (pBlendState10 != NULL)	{
		pBlendState10->Release();
		pBlendState10 = NULL;
	}

    // release the ID3DX10Sprite object
    if (pSpriteObject)    {
        pSpriteObject->Release();
        pSpriteObject = NULL;
    }

	// Release the game font
	if (pGameFont) { 
		pGameFont->Release();
		pGameFont = NULL;
	}

	// release the rendertarget
	if (pRenderTargetView) 	{
		pRenderTargetView->Release();
	}

	// release the swapchain
    if (pSwapChain)	{
		pSwapChain->Release();
	}

	// release the D3D Device
    if (pD3DDevice)	{
		pD3DDevice->Release();
	}
} // ShutdownDirect3D

void DX::InitiateDefaultBlend(D3D10_BLEND_DESC* StateDesc) {
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
