#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "RenderWindow.hpp"
#include "tools.hpp"

bool RenderWindow::Event()
{
	SDL_Event event;
	bool isRunning = true;

	while (SDL_PollEvent(&event))
		switch (event.type)
		{
			case SDL_KEYUP:
				isRunning = this->KeyUp(&event);
				break;
			case SDL_KEYDOWN:
				isRunning = this->KeyDown(&event);
				break;
			case SDL_MOUSEBUTTONDOWN:
				isRunning = this->MouseDown(&event);
				break;
			case SDL_QUIT:
				return false;
				break;
		}
	return isRunning;
}

bool RenderWindow::KeyDown(SDL_Event *event)
{
	switch (event->key.keysym.sym)
	{
		case SDLK_z:
			keys[KEY::Z] = true;
			break;
		case SDLK_q:
			keys[KEY::Q] = true;
			break;
		case SDLK_d:
			keys[KEY::D] = true;
			break;
		case SDLK_s:
			keys[KEY::S] = true;
			break;
	}
	return true;
}

bool RenderWindow::KeyUp(SDL_Event *event)
{
	switch (event->key.keysym.sym)
	{
		case SDLK_z:
			keys[KEY::Z] = 0;
			break;
		case SDLK_q:
			keys[KEY::Q] = 0;
			break;
		case SDLK_d:
			keys[KEY::D] = 0;
			break;
		case SDLK_s:
			keys[KEY::S] = 0;
			break;
	}
	return true;
}

bool RenderWindow::isPressed(int indice)
{
	return keys[indice];
}

bool RenderWindow::MouseDown(SDL_Event *event)
{
	switch (event->button.button)
	{
		case SDL_BUTTON_LEFT:
			if (event->motion.x > (WIN_W - NB_TILE * TILE_W))
			{
				int x = (event->motion.x - (WIN_W - NB_TILE * TILE_W)) / TILE_W;
				int y = event->motion.y / TILE_H;
				layer[0].SetID(y * NB_TILE + x);
			}
			else
				layer[0].Set((event->motion.x + camera.x) / TILE_W, (event->motion.y + camera.y) / TILE_H);
			break;
	}
	return true;
}
