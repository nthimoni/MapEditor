#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>


#include "RenderWindow.hpp"
#include "constantes.hpp"
#include "usage.hpp"
#include "init.hpp"
#include "IOFile.hpp"

int main(int argc, char *argv[])
{
	if (!usage(argc))
		return (0);
	if (!Init())
		return (0);

	RenderWindow window(TITLE, WIN_W, WIN_H);
	ReadFiles(argv, &window);

	while (window.Event())
	{
		window.MoveCamera();
		window.Clear();
		window.PrintBackground();
		window.PrintMap();
		window.PrintBurgers();
		window.PrintTileset();
		window.PrintRect();
		window.Render();
	}

	WriteFiles(argv, &window);
	Quit();
	return (0);
}
