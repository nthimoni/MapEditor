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
	: window(NULL), renderer(NULL), background(NULL), keys(4, false), font(NULL)
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
	camera.x = pos->x;
	camera.y = pos->y;
}

void RenderWindow::setCameraX(int x)
{
	camera.x = x;
}

void RenderWindow::setCameraY(int y)
{
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
	SDL_RenderCopy(this->renderer, this->background, NULL, NULL);
}

void RenderWindow::LoadFont(const char *font_path, int size)
{
	if (this->font != nullptr)
		TTF_CloseFont(this->font);
	this->font = TTF_OpenFont(font_path, size);
}

void RenderWindow::LoadBurgerSound(const char *sound_path)
{
	burgers.LoadBurgerSound(sound_path);
}

RenderWindow::~RenderWindow()
{
	TTF_CloseFont(this->font);
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_DestroyTexture(this->background);
}