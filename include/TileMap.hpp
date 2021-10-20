#ifndef TILEMAP_HPP
# define TILEMAP_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <vector>

#include "constantes.hpp"
#include "tools.hpp"

class TileMap
{
	public:
		TileMap(const char *text_path, const char *tab_path, SDL_Renderer *p_renderer);
		void LoadTab(const char *p_path);
		void LoadTexture(const char *p_path);
		void LoadRenderer(SDL_Renderer *p_renderer);
		void Display(SDL_Rect *camera);
		SDL_Texture  *GetTexture();
		tile_id Get(int x, int y);
		void Set(int x, int y);
		void SetIdMap(SDL_Rect selection);
		void SetIdTileset(SDL_Rect selection);
		void save(const char *path_map);
		~TileMap();
	private:
		std::vector<std::vector<tile_id>> ID;
		SDL_Texture *text;
		SDL_Renderer *renderer;
		std::vector<std::vector<tile_id>> tab;
		void ParseLine(std::string line);

};

#endif
