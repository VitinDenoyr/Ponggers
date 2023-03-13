#pragma once
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#include <vector>
#include "Mathematics.hpp"
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Ingame.hpp"
#include "Menu.hpp"
#include "Settings.hpp"

static const int SCREENWIDTH = 960, SCREENHEIGHT = 540;
bool pong(RenderWindow &window, Game &game);