#include "..\window\window.h"
#include "..\graphics\graphics.h"
#include "..\game\game.h"

void main(void)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Window window; Graphics graphics; Game game;
	
	graphics.set_window(&window);

	if (window.Initalize() && graphics.Initialize() && game.Initalize())
		while (window.Run() && graphics.Begin() && game.Run() && graphics.End());

	game.Finalize(); graphics.Finalize(); window.Finalize();
}