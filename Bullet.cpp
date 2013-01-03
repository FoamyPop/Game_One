#include "Bullet.h"

Bullet::Bullet(int DIRECTION, Player* player)
{
	direction = DIRECTION;
	alive = true;
	src = IMG_Load("Game_Data\\Images\\Bullet.png");
	pos.x = player->pos.x + ((player->pos.w / 2) - (src->w / 2));
	pos.y = player->pos.y + ((player->pos.h / 2) - (src->h / 2));
	speed = 7;
}

void Bullet::Update()
{
	if(pos.y >= 1100 && pos.y <= 0 && pos.x <= 0 && pos.x >= 2000)
	{
		alive = false;
	}

	if(pos.x == 0 || pos.y ==0)
		alive = false;

	if(alive)
	{
		SDL_BlitSurface(src, 0, SDL_GetVideoSurface(), &pos);
		
		switch(direction)
		{
			case UP:
				pos.y -= speed;
				break;
			case DOWN:
				pos.y += speed;
				break;
			case LEFT:
				pos.x -= speed;
				break;
			case RIGHT:
				pos.x += speed;
				break;
		}
		
	}
}


Bullet::~Bullet(void)
{
}
