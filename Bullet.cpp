#include "Bullet.h"

Bullet::Bullet(int DIRECTION, Player& player)
{
	direction = DIRECTION;
	alive = true;
	src = new IMAGE("Images\\Bullet.png", player.src->x, player.src->y);
	src->x = player.src->x + ((player.src->w / 2) - (src->w / 2));
	src->y = player.src->y + ((player.src->h / 2) - (src->h / 2));
	speed = 9;
}

void Bullet::Update(sf::RenderWindow &window)
{
	if(src->y >= 1100 && src->y <= 0 && src->x <= 0 && src->x >= 2000)
	{
		alive = false;
	}

	if(src->x == 0 || src->y == 0)
		alive = false;

	if(alive)
	{
		/* DRAW HERE */
		src->draw(window);
		/* UPDATE POS OF BULLET */		
		switch(direction)
		{
			case UP:
				src->SetPosition(src->x, src->y - speed);
				break;
			case DOWN:
				src->SetPosition(src->x, src->y + speed);
				break;
			case LEFT:
				src->SetPosition(src->x - speed, src->y);
				break;
			case RIGHT:
				src->SetPosition(src->x + speed, src->y);
				break;
		}		
	}
}


Bullet::~Bullet(void)
{

}
