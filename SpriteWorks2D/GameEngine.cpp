#include "stdafx.h"
#ifdef RENDER_ENG_DX 
#include "DirectXMain.h"
#endif


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	// Check any available messages from the queue
	switch (message)
	{ 
		// allow the user to press the escape key to end the application
	case WM_KEYDOWN:
		switch(wParam) 
		{
		// check if the user hit the Escape key
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


SW2D::SWDevice::SWDevice ( void ) { 
}

HWND* SW2D::SWDevice::GetWindowHandle ( void ) { 
	return &(this->hWnd);
}

bool SW2D::SWDevice::CreateGameWindow ( HINSTANCE hInstance, int width, int height) { 
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize			= sizeof(WNDCLASSEX);		    // the size of the structure
	wcex.style			= CS_HREDRAW | CS_VREDRAW;  
	wcex.lpfnWndProc	= (WNDPROC)WndProc;			    // The window procedure callback
	wcex.cbClsExtra		= 0;							// Extra bytes to allocate for this class
	wcex.cbWndExtra		= 0;							// Extra bytes to allowcate for this instance
	wcex.hInstance		= hInstance;
	wcex.hIcon			= 0;							// Icon to associate with the application
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);	// The default cursor to use
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);   // Background color
	wcex.lpszMenuName	= NULL;						    // The resource name of the menu (if I had one...)
	wcex.lpszClassName	= CLASS_NAME;			        // Name of the class being created
	wcex.hIconSm		= 0;							// Handle of the small icon
	if (!RegisterClassEx(&wcex)) {
		return false;
	}
	
	// Resize the window
	RECT rect = { 0, 0, width, height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// Create the window from the class above
	this->hWnd = CreateWindow(CLASS_NAME, 
		CLASS_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd) { 
		return false;
	}

	// Display the window on the screen
	ShowWindow(this->hWnd, SW_SHOW);
	UpdateWindow(this->hWnd);

	return true;
}


void SW2D::SWDevice::InitInterface ( void ) { 
#ifdef RENDER_ENG_DX
	
#endif
}