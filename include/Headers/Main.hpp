#pragma once
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#include <vector>
#include "Menu.hpp"
#include "Pong.hpp"
/*
#include "Pong.hpp"
#include "Math.hpp"
#include "Entity.hpp"
#include "Ingame.hpp"
#include "Menu.hpp"
#include "Mixer.hpp"
#include "Settings.hpp"
#include "Controls.hpp"
*/
//Definições
#define FAIL_SDL != 0
#define FAIL_IMG == 0
#define FAIL_TTF != 0
#define FAIL_MIX == 0