#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "RenderWindow.hpp"
#include "constantes.hpp"
#include "usage.hpp"
#include "init.hpp"

int main(int argc, char *argv[])
{
	(void)argv;
	if (!usage(argc))
		return (0);
	if (!Init())
		return (0);

	Quit();
	return (0);
}
