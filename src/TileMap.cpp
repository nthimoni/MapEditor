#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include "constantes.hpp"
#include "TileMap.hpp"

TileMap::TileMap(const char *text_path, const char *tab_path, SDL_Renderer *p_renderer)
	:text(NULL), renderer(p_renderer)
{
	this->LoadTab(tab_path);
	this->LoadTexture(text_path);
	ID.emplace_back();
	ID[0].emplace_back(0);
}

void TileMap::LoadTab(const char *p_path)
{
	tab.clear();
	std::ifstream file(p_path);
	std::string buffer;

	if (!file.is_open())
		std::cout << "(LoadTab) Erreur lors de l'ouverture de : " << p_path << '\n';
	else
		while (std::getline(file, buffer))
			this->ParseLine(buffer);
	file.close();
}

void TileMap::LoadTexture(const char *p_path)
{
	if (this->text != NULL)
		SDL_DestroyTexture(this->text);
	this->text = IMG_LoadTexture(this->renderer, p_path);
	if (this->text == NULL)
		std::cout << "(LoadText) Erreur lors du chargement de : " << p_path << std::endl;
}

void TileMap::LoadRenderer(SDL_Renderer *p_renderer)
{
	this->renderer = p_renderer;
}

void TileMap::ParseLine(std::string line)
{
	tile_id a = 0;
	std::string buffer;
	std::istringstream s_line(line);

	tab.emplace_back();
	while (std::getline(s_line, buffer, '\t'))
	{
		a = (tile_id)std::atoi(buffer.c_str());
		tab[tab.size() - 1].emplace_back(a);
	}
}

tile_id TileMap::Get(int x, int y)
{
	if (x < 0 || y < 0)
		return 0;
	if ((unsigned int)y >= tab.size())
		return 0;
	if ((unsigned int)x >= tab[y].size())
		return 0;
	return tab[y][x];
}

void TileMap::Display(SDL_Rect *camera)
{
	SDL_Rect src;
	SDL_Rect dst;

	src.w = TILE_W;
	src.h = TILE_H;
	dst.w = TILE_W;
	dst.h = TILE_H;

	for (unsigned int i = 0 ; i < tab.size() ; i++)
		for(unsigned int a = 0 ; a < tab[i].size() ; a++)
		{

			src.x = (tab[i][a] % NB_TILE) * TILE_W;
			src.y = (tab[i][a] / NB_TILE) * TILE_H;
			dst.x = a * TILE_W - camera->x;
			dst.y = i * TILE_H - camera->y;
			SDL_RenderCopy(renderer, text, &src, &dst);
		}
}

SDL_Texture *TileMap::GetTexture()
{
	return text;
}

void TileMap::Set(int x, int y)
{
	if (x < 0 || y < 0)
		return;
	for (unsigned int u = 0; u < ID.size(); u++)
	{
		for (unsigned int i = 0; i < ID[u].size(); i++)
		{
		while (y + (int)i >= (int)tab.size())
			tab.emplace_back();
		while (x + (int)u >= (int)tab[y + i].size())
			tab[y + i].emplace_back();
		tab[y + i][x + u] = ID[u][i];
		}
	}
}

void TileMap::SetIdMap(SDL_Rect selection)
{
	ID.clear();
	for (int i = selection.x / TILE_W; i <= (selection.x + selection.w) / TILE_W; i++)
	{

		ID.emplace_back();
		for (int u = selection.y / TILE_H; u <= (selection.y + selection.h) / TILE_H; u++)
			ID[i - selection.x / TILE_W].emplace_back(this->Get(i, u));
	}
}

void TileMap::SetIdTileset(SDL_Rect selection)
{
	ID.clear();
	for (int i = selection.x / TILE_W; i <= (selection.x + selection.w) / TILE_W; i++)
	{
		ID.emplace_back();
		for (int u = selection.y / TILE_H; u <= (selection.y + selection.h) / TILE_H; u++)
			ID[i - selection.x / TILE_W].emplace_back(u * NB_TILE + i);
	}
}

void TileMap::save(const char *path_map)
{
	std::ofstream file(path_map, std::ofstream::trunc);
	for (unsigned int i = 0; i < tab.size(); i++)
	{
		if (i != 0)
			file << '\n';
		for (unsigned int u = 0; u < tab[i].size(); u++)
		{
			if (u != 0)
				file << '\t';
			if (tab[i][u] != 0)
				file << tab[i][u];
		}
	}
}

TileMap::~TileMap()
{
	SDL_DestroyTexture(text);
}
