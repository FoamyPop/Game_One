#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include <vector>
#include "Bullet.h"
#include "Player.h"

class Enemy
{
public:
	Enemy(int x, int y, Player* p);
	~Enemy(void);
	void Update(std::vector<Bullet*>& bullets);
	int getHealth()
	{
		return health;
	}
	void damage(int amount);
	void DIE();
	bool alive;
	SDL_Rect pos;
private:
	SDL_Surface* src;
	Player* player;
	SDL_Surface* msg;	
	SDL_Rect textPos;
	int health;
	TTF_Font* font;
	SDL_Color color;
	SDL_Rect viewRect;
	Uint32 start;	
	int speed;
};