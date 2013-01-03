#include "Player.h"

Player::Player(int x, int y)
{
	src = IMG_Load("Game_Data\\Images\\Player.png");
	pos.x = x;
	pos.y = y;
	speed = 5;
	move[0] = false;
	move[1] = false;
	move[2] = false;
	move[3] = false;
	health = 100;
	armour = 100;
	SCORE = 0;
}

void Player::damage(int value)
{
	health -= value;
}

void Player::Update(std::vector<Enemy*> enemies)
{
	for(int i = 0; i < enemies.size(); i++)
	{
		if(enemies[i]->pos.x <= pos.x + pos.w && enemies[i]->pos.x >= pos.x &&
			   enemies[i]->pos.y <= pos.y + pos.h && enemies[i]->pos.y >= pos.y)
			{
				if(enemies[i]->alive)
				{
					damage(5);
				}
			}
	}
}

void Player::Draw(int WIDTH, int HEIGHT)
{
	if(move[0])
		if(pos.y > 0) pos.y -= speed;
	if(move[1])
		if(pos.x > 0) pos.x -= speed;
	if(move[2])
		if(pos.y < HEIGHT - pos.h) pos.y += speed;
	if(move[3])
		if(pos.x < WIDTH - pos.w) pos.x += speed;
	SDL_BlitSurface(src, 0, SDL_GetVideoSurface(), &pos);
}

Player::~Player(void)
{

}
