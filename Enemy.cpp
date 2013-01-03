#include "Enemy.h"

Enemy::Enemy(int x, int y, Player* p)
{
	font = TTF_OpenFont("Game_Data\\HUD-Font.ttf", 20);
	src = IMG_Load("Game_Data\\Images\\Enemy.png");
	start = SDL_GetTicks();

	player = p;

	color.r = 255;
	color.g = 20;
	color.b = 0;

	viewRect.x = 0;
	viewRect.y = 0;
	viewRect.w = 50;
	viewRect.h = 50;

	speed = 6;

	msg = TTF_RenderText_Solid(font, std::to_string(health).c_str(), color);

	pos.x = x;
	pos.y = y;
	textPos.y = pos.y - 16;
	textPos.x  = pos.x + 6;
	health = 100;	
	alive = true;
}

void Enemy::damage(int amount)
{
	if(health > 0)
		health -= amount;
}

void Enemy::Update(std::vector<Bullet*>& bullets)
{
	//LOGIC
	if(alive)
	{
		if(health <= 0)
			DIE();
		for(int i = 0; i < bullets.size(); i++)
		{
			if(bullets[i]->pos.x <= pos.x + pos.w && bullets[i]->pos.x >= pos.x &&
			   bullets[i]->pos.y <= pos.y + pos.h && bullets[i]->pos.y >= pos.y)
			{
				if(bullets[i]->alive)
				{
					bullets[i]->alive = false;
					damage(20);	
				}
			}
		}

		//DRAW
		msg = TTF_RenderText_Solid(font, std::to_string(health).c_str(), color);
		textPos.y = pos.y - 16;
		textPos.x  = pos.x + 6;
		SDL_BlitSurface(msg,  0, SDL_GetVideoSurface(), &textPos);
	}
		SDL_BlitSurface(src,  &viewRect, SDL_GetVideoSurface(), &pos);		
}

void Enemy::DIE()
{
	src = IMG_Load("Game_Data\\Images\\Grave.png");
	alive = false;
	player->SCORE += 100;
}

Enemy::~Enemy(void)
{
	SDL_FreeSurface(src);
	SDL_FreeSurface(msg);
}
