#include <SDL2/SDL.h>

#include <cstdlib>
#include <string>

#include "RenderWindow.hpp"

void ReadFiles(char *argv[], RenderWindow *window)
{
	std::string lvlfolder = "level/";
	std::string assets_folder = "assets/";
	std::string level = argv[1];
	std::string burger_text = assets_folder + "burger.png";
	std::string burger_map = lvlfolder + level + "/BurgerMap.txt";
	std::string bg_text = assets_folder + argv[3];
	std::string tileset = assets_folder + argv[2];
	std::string tilemap = lvlfolder + level + "/Map.txt";

	window->SetLevel(std::atoi(argv[1]));
	window->LoadBurgers(burger_text.c_str(), burger_map.c_str());
	window->LoadBackground(bg_text.c_str());
	window->AddLayer(tileset.c_str(), tilemap.c_str());
}

void WriteFiles(char *argv[], RenderWindow *window)
{
	(void)argv;
	window->save();
	return;
}
