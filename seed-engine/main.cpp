#include <vector>
#include <iostream>

#include "..\simple-window\simple-window.h"
#include "..\directx11\directx11.h"

void main(void)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	ConnectedPointer<int> a(5);
	ConnectedPointer<int> b(a);

	a.Release();
	
	std::cout << "a: ";
	if (a.isExpired())
	{
		std::cout << "Expired." << std::endl;
	}
	else
	{
		std::cout << *a << std::endl;
	}
	std::cout << "b: ";
	if (b.isExpired())
	{
		std::cout << "Expired." << std::endl;
	}
	else
	{
		std::cout << *b << std::endl;
	}

	rewind(stdin);
	getchar();

	//ConnectedPointer<Window> window(0);
	//window.Reset<SimpleWindow>();
	//ConnectedPointer<Graphics> graphics(0);
	//graphics.Reset<DirectX11>();

	//int a = 10;
	//int b = a;
	//b = a;

	//window->Initalize();
	//graphics->Initialize();

	//while (window->Run() && graphics->Begin() && graphics->End());

	//graphics->Finalize();
	//window->Finalize();
}