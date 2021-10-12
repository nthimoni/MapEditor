#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

bool Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init has failed. SDL_ERROR : " << SDL_GetError() << std::endl;
		return false;
	}
	if (!IMG_Init(IMG_INIT_PNG))
	{
		std::cout << "IMG_Init (png) has failed. SDL_ERROR : " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}
	if (!IMG_Init(IMG_INIT_JPG))
	{
		std::cout << "IMG_Init (jpg) has failed. SDL_ERROR : " << SDL_GetError() << std::endl;
		IMG_Quit();
		SDL_Quit();
		return false;
	}
	return true;
}

void Quit()
{
	IMG_Quit();
	SDL_Quit();
}
