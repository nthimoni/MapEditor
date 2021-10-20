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
			case SDL_MOUSEBUTTONUP:
				isRunning = this->MouseUp(&event);
				break;
			case SDL_MOUSEWHEEL:
				yTileSet += event.wheel.y * 10;
				if (yTileSet > 0)
					yTileSet = 0;
				int h;
				SDL_QueryTexture(layer[0].GetTexture(), NULL, NULL, NULL, &h);
				if (yTileSet < WIN_H - h)
					yTileSet = WIN_H - h;
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
		case SDLK_SPACE:
			if (!nextBurger)
				nextBurger = true;
			else
				nextBurger = false;
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
				start_selec.x = event->motion.x - (WIN_W - NB_TILE * TILE_W);
				start_selec.y = event->motion.y - yTileSet;
				nextBurger = false;
			}
			else
			{
				if (!nextBurger)
					layer[0].Set((event->motion.x + camera.x) / TILE_W, 
									(event->motion.y + camera.y) / TILE_H);
				else
					burgers.Change((event->motion.x + camera.x) / TILE_W,
									(event->motion.y + camera.y) / TILE_H);
			}
			break;
		case SDL_BUTTON_RIGHT:
			start_selec.x = event->motion.x + camera.x;
			start_selec.y = event->motion.y + camera.y;
			nextBurger = false;
			break;
	}
	return true;
}

bool RenderWindow::MouseUp(SDL_Event *event)
{
	switch (event->button.button)
	{
		case SDL_BUTTON_RIGHT:
			nextBurger = false;
			if (start_selec.x <= event->motion.x + camera.x)
			{
				selection.x = start_selec.x;
				selection.w = event->motion.x + camera.x - start_selec.x;
			}
			else
			{
				selection.x = event->motion.x + camera.x;
				selection.w = start_selec.x - (event->motion.x + camera.x);
			}
			if (start_selec.y <= event->motion.y + camera.y)
			{
				selection.y = start_selec.y;
				selection.h = (event->motion.y + camera.y) - start_selec.y;
			}
			else
			{
				selection.y = event->motion.y + camera.y;
				selection.h = start_selec.y - (event->motion.y + camera.y);
			}
			layer[0].SetIdMap(selection);
			break;
		case SDL_BUTTON_LEFT:
			if (event->motion.x > (WIN_W - NB_TILE * TILE_W))
			{
				nextBurger = false;
				int actualX = event->motion.x - (WIN_W - NB_TILE * TILE_W);
				int actualY = event->motion.y - yTileSet;
				if (start_selec.x <= actualX)
				{
					selection.x = start_selec.x;
					selection.w = actualX - start_selec.x;
				}
				else
				{
					selection.x = actualX;
					selection.w = start_selec.x - actualX;
				}
				if (start_selec.y <= actualY)
				{
					selection.y = start_selec.y;
					selection.h = actualY - start_selec.y;
				}
				else
				{
					selection.y = actualY;
					selection.h = start_selec.y - actualY;
				}
				layer[0].SetIdTileset(selection);
			}
			break;

	}
	return true;
}

