#pragma once
//SDL
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
//Padrão
#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#include <vector>
//Manuais
#include "Pong.hpp"
#include "Mathematics.hpp"
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Ingame.hpp"
#include "Menu.hpp"
#include "Settings.hpp"
#include "Controls.hpp"
//Definições
#define FAIL_SDL != 0
#define FAIL_IMG == 0
#define FAIL_TTF != 0