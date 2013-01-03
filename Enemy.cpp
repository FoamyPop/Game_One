#include "Enemy.h"

Enemy::Enemy(int x, int y, Player& p)
{
	src = new IMAGE("Images\\Enemy.png", x, y);
	speed = 6;
	health = 100;	
	alive = true;
	display = new STRING(std::to_string(health), x, y - 30, sf::Color(255, 20, 0));
	display->setSize(26);
	timer.Reset();
	lifetime = 10;
}

void Enemy::damage(int amount)
{
	if(health > 0)
		health -= amount;
}

void Enemy::Update(sf::RenderWindow &window, std::vector<Bullet*> &bullets, Player& player)
{
	//LOGIC
	if(alive)
	{
		display = new STRING(std::to_string(health), src->x, src->y - 30, sf::Color(255, 20, 0));
		display->setSize(26);

		if(health <= 0)
			DIE(player);
		for(int i = 0; i < bullets.size(); i++)
		{
			if(bullets[i]->alive)
			{
				if(bullets[i]->src->x <= src->x + src->w &&
				   bullets[i]->src->x >= src->x &&
				   bullets[i]->src->y <= src->y + src->h &&
				   bullets[i]->src->y >= src->y)
				{
					bullets[i]->alive = false;
					damage(20);
				}
			}
		}
		display->Draw(window);
		timer.Reset();
	}	
	src->draw(window);
}

bool Enemy::dead()
{
	if(timer.GetElapsedTime() > lifetime)
	{
		return true;
	}
	return false;
}

void Enemy::DIE(Player& player)
{
	src = new IMAGE("Images\\Grave.png", src->x, src->y);
	alive = false;
	/* ADD SCORE TO PLAYER */
	player.SCORE += 100;
}

Enemy::~Enemy(void)
{

}
