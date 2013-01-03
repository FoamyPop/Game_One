#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Enemy.h"
#include <vector>

class Player
{
public:
	Player(int x, int y);
	~Player(void);
	void Draw(int WIDTH, int HEIGHT);
	int health;
	int armour;
	bool move[4];
	SDL_Surface* src;
	SDL_Rect pos;
	int speed;	
	int SCORE;
	void damage(int value);
	void Update(std::vector<Enemy*> enemies);
};
