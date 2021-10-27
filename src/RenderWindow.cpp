#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <vector>
#include <string>

#include "RenderWindow.hpp"
#include "TileMap.hpp"
#include "tools.hpp"

RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
	:nextBurger(false), yTileSet(0), window(NULL), renderer(NULL), background(NULL), keys(4, false), font(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (!window)
		std::cout << "Window failed to init. SDL_ERROR : " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	camera.x = 0;
	camera.y = 0;
	camera.w = WIN_W;
	camera.h = WIN_H;
}

void RenderWindow::AddLayer(const char *p_text, const char *p_tab)
{
	layer.emplace_back(p_text, p_tab, this->renderer);
}

void RenderWindow::PrintMap()
{
	for (unsigned int i = 0; i < layer.size(); i++)
		layer[i].Display(&camera);
}

void RenderWindow::LoadBurgers(const char *texture, const char *tab)
{
	burgers.LoadRenderer(renderer);
	burgers.LoadTab(tab);
	burgers.LoadTexture(texture);
}

void RenderWindow::PrintBurgers()
{
	burgers.Display(&camera);
}

void RenderWindow::Clear()
{
	SDL_RenderClear(this->renderer);
}

void RenderWindow::Render()
{
	SDL_RenderPresent(this->renderer);
}

void RenderWindow::setCamera(Vector2 *pos)
{
	this->setCameraX(pos->x);
	this->setCameraY(pos->y);
}

void RenderWindow::setCameraX(int x)
{
	if (x >= 0)
		camera.x = x;
}

void RenderWindow::setCameraY(int y)
{
	if (y >= 0)
		camera.y = y;
}

void RenderWindow::LoadBackground(const char *bgtext)
{
	if (background != NULL)
		SDL_DestroyTexture(background);
	background = IMG_LoadTexture(this->renderer, bgtext);
	if (background == NULL)
		std::cout << "Erreur lors du chargement de " << bgtext << '\n';
}

void RenderWindow::PrintBackground()
{
	SDL_Rect dst;
	dst.x = 0;
	dst.y = 0;
	SDL_QueryTexture(background, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(this->renderer, this->background, NULL, &dst);
}

void RenderWindow::SetLevel(int level)
{
	this->level = level;
}

void RenderWindow::MoveCamera()
{
	if (keys[KEY::Z])
		camera.y -= CAMERA_SPEED;
	if (keys[KEY::S])
		camera.y += CAMERA_SPEED;
	if (keys[KEY::Q])
		camera.x -= CAMERA_SPEED;
	if (keys[KEY::D])
		camera.x += CAMERA_SPEED;
	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
}

void RenderWindow::PrintTileset()
{
	SDL_Rect dst;
	dst.y = yTileSet;
	dst.x = WIN_W - NB_TILE * TILE_W;
	SDL_QueryTexture(layer[0].GetTexture(), NULL, NULL, &dst.w, &dst.h);
	SDL_RenderFillRect(renderer, &dst);
	SDL_RenderCopy(this->renderer, layer[0].GetTexture(), NULL, &dst);
}

void RenderWindow::PrintRect()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect rect;
	SDL_GetMouseState(&rect.x, &rect.y);
	if (rect.x > (WIN_W - NB_TILE * TILE_W))
	{
		rect.x -= (WIN_W - NB_TILE * TILE_W);
		rect.x /= TILE_W;
		rect.x *= TILE_W;
		rect.x += (WIN_W - NB_TILE * TILE_W);
		rect.y -= yTileSet;
		rect.y /= TILE_H;
		rect.y *= TILE_H;
		rect.y += yTileSet;
	}
	else
	{
		rect.x += camera.x;
		rect.x /= TILE_W;
		rect.x *= TILE_W;
		rect.x -= camera.x;
		rect.y += camera.y;
		rect.y /= TILE_H;
		rect.y *= TILE_H;
		rect.y -= camera.y;
	}
	rect.w = TILE_W;
	rect.h = TILE_H;
	SDL_RenderDrawRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void RenderWindow::save()
{
	layer[0].save("level/1/Map.txt");
	burgers.save("level/1/BurgerMap.txt");
}

RenderWindow::~RenderWindow()
{
	TTF_CloseFont(this->font);
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_DestroyTexture(this->background);
}
