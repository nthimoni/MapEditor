#ifndef IOFILE_HPP
# define IOFILE_HPP

#include <SDL2/SDL.h>

#include "RenderWindow.hpp"

void ReadFiles(char *argv[], RenderWindow *window);
void WriteFiles(char *argv[], RenderWindow *window);

#endif
