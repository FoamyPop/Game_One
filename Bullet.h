#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Player.h"
#include <cstdlib>

#ifndef _BULLET_H
#define _BULLET_H

class Bullet
{
public:
	Bullet(int DIRECTION, Player* player);
	~Bullet(void);
	void Update();
	SDL_Surface* src;
	SDL_Rect pos;
	int direction;
	int speed;
	bool alive;
	int rnd;
	enum DIRECTIONS
	{
		UP, DOWN, LEFT, RIGHT
	};
};

#endif

