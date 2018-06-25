#include "..\window\window.h"
#include "..\graphics\graphics.h"
#include "..\game\game.h"

#ifdef _DEBUG
int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#endif
	Window window; Graphics graphics; Game game;
	
	graphics.set_window(&window);
	
	if (window.Initalize() && graphics.Initialize() && game.Initalize())
		while (window.Run() && graphics.Begin() && game.Run() && graphics.End());

	game.Finalize(); graphics.Finalize(); window.Finalize();
} 