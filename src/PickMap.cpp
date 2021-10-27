#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Pickable.hpp"
#include "PickMap.hpp"
#include "tools.hpp"
#include "constantes.hpp"

PickMap::PickMap() : tab(), renderer(NULL), texture(NULL), music(NULL)
{
}

void PickMap::LoadTab(const char *TabPath)
{
	this->FreeTab();
	std::ifstream file(TabPath);
	std::string buffer;

	if (!file.is_open())
		std::cout << "Erreur lors de l'ouverture de : " << TabPath << '\n';
	else
		while(std::getline(file, buffer))
			this->ParseLine(buffer);
	file.close();
}

void PickMap::ParseLine(std::string line)
{
	int a = 0;
	std::string buffer;
	std::istringstream s_line(line);
	SDL_Rect obj;

	tab.emplace_back();
	while (std::getline(s_line, buffer, '\t'))
	{
		obj.x = tab[tab.size() - 1].size() * BURGER_W;
		obj.y = (tab.size() - 1) * BURGER_H;
		obj.w = BURGER_W;
		obj.h = BURGER_H;
		a = std::atoi(buffer.c_str());
		if (a != 0)
			tab[tab.size() - 1].emplace_back(new Pickable(&obj));
		else 
			tab[tab.size() - 1].emplace_back(nullptr);
	}
}

void PickMap::LoadTexture(const char *TexturePath)
{
	if (texture != NULL)
		SDL_DestroyTexture(texture);
	texture = IMG_LoadTexture(renderer, TexturePath);
	if (texture == NULL)
		std::cout << "Erreur lors du chargement de : " << TexturePath << '\n';
}

void PickMap::LoadRenderer(SDL_Renderer *p_renderer)
{
	this->renderer = p_renderer;
}

void PickMap::Display(SDL_Rect *camera)
{
	for (unsigned int i = 0; i < tab.size(); i++)
		for (unsigned int u = 0; u < tab[i].size(); u++)
			if (tab[i][u] != NULL)
				tab[i][u]->display(this->renderer, this->texture, camera);
}

void PickMap::FreeTab()
{
	for (unsigned int i = 0; i < tab.size(); i++)
		for (unsigned int u = 0; u < tab[i].size(); u++)
			if (tab[i][u] != NULL)
				delete tab[i][u];
	tab.clear();
}

bool PickMap::pickUp(int x, int y)
{
	if (y < 0 || y > (int)tab.size() - 1)
		return false;
	if (x < 0 || x > (int)tab[y].size() - 1)
		return false;
	if (tab[y][x] == NULL)
		return false;
	delete tab[y][x];
	tab[y][x] = NULL;
	Mix_PlayMusic(music, 1);
	return true;
}

void PickMap::LoadBurgerSound(const char *sound_path)
{
	if (music != nullptr)
		Mix_FreeMusic(music);
	music = Mix_LoadMUS(sound_path);
}

void PickMap::Change(int x, int y)
{
	while (y >= (int)tab.size())
		tab.emplace_back();
	while (x >= (int)tab[y].size())
		tab[y].emplace_back(nullptr);
	if (tab[y][x] == nullptr)
	{
		SDL_Rect obj;
		obj.x = x * BURGER_W;
		obj.y = y * BURGER_H;
		obj.w = BURGER_W;
		obj.h = BURGER_H;

		tab[y][x] = new Pickable(&obj);
	}
	else
	{
		delete tab[y][x];
		tab[y][x] = nullptr;
	}
}

void PickMap::save(const char *pathFile)
{
	std::ofstream file(pathFile, std::ofstream::trunc);
	for (unsigned int i = 0; i < tab.size(); i++)
	{
		if (i != 0)
			file << '\n';
		for (unsigned int u = 0; u < tab[i].size(); u++)
		{
			if (u != 0)
				file << '\t';
			if (tab[i][u] != nullptr)
				file << 1;
		}
	}
}

PickMap::~PickMap()
{
	SDL_DestroyTexture(texture);
	this->FreeTab();
}
