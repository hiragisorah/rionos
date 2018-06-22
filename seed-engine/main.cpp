#include <vector>
#include <iostream>

#include "..\simple-window\simple-window.h"
#include "..\directx11\directx11.h"

void main(void)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	ConnectedPointer<Window> window(new SimpleWindow);
	ConnectedPointer<Graphics> graphics(new DirectX11);

	graphics->set_window(&window);

	window->Initalize();
	graphics->Initialize();

	while (window->Run() && graphics->Begin() && graphics->End());

	graphics->Finalize();
	window->Finalize();
}