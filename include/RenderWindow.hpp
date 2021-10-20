#ifndef RENDERWINDOW_HPP
# define RENDERWINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <vector>

#include "TileMap.hpp"
#include "PickMap.hpp"

namespace KEY
{
	enum
	{
		Z = 0,
		Q,
		S,
		D
	};
};

class RenderWindow
{
	public:
		RenderWindow(const char *p_title, int p_w, int p_h);
		void AddLayer(const char *p_text, const char *p_tab);
		void PrintMap();
		bool Event();
		bool isPressed(int indice);
		void Clear();
		void Render();
		void setCamera(Vector2 *pos);
		void setCameraX(int x);
		void setCameraY(int y);
		void LoadBackground(const char *bgtext);
		void LoadBurgers(const char *texture, const char *tab);
		void PrintBurgers();
		void PrintBackground();
		void SetLevel(int level);
		void MoveCamera();
		void PrintTileset();
		void PrintRect();
		void save();
		~RenderWindow();
	private:
		bool nextBurger;
		int yTileSet;
		SDL_Rect selection;
		Vector2 start_selec;
		int level;
		SDL_Rect camera;
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Texture *background;
		std::vector<TileMap> layer;
		PickMap burgers;
		std::vector<bool> keys;
		TTF_Font *font;
	private:
		bool KeyDown(SDL_Event *event);
		bool KeyUp(SDL_Event *event);
		bool MouseDown(SDL_Event *event);
		bool MouseUp(SDL_Event *event);
};

#endif
