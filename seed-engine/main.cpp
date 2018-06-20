#include <vector>
#include <iostream>

#include "..\simple-window\simple-window.h"
#include "..\directx11\directx11.h"

void main(void)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	ConnectedPointer<Window> window(0);
	window.Reset<SimpleWindow>();
	ConnectedPointer<Graphics> graphics(0);
	graphics.Reset<DirectX11>();

	window->Initalize();
	graphics->Initialize();

	while (window->Run() && graphics->Begin() && graphics->End());

	graphics->Finalize();
	window->Finalize();
}