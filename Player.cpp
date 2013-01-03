#include "Player.h"

Player::Player(int x, int y)
{
	src = new IMAGE("Images\\Player.png", x, y);
	speed = 5;
	health = 100;
	armour = 100;
	SCORE = 0;
	move[0] = false;
	move[1] = false;
	move[2] = false;
	move[3] = false;
}

void Player::damage(int value)
{
	health -= value;
}

void Player::Draw(sf::RenderWindow &window)
{
	if(move[0])
		src->SetPosition(src->x, src->y - speed); 
	if(move[1])
		src->SetPosition(src->x, src->y + speed); 
	if(move[2])
		src->SetPosition(src->x - speed, src->y); 
	if(move[3])
		src->SetPosition(src->x + speed, src->y); 

	src->draw(window);
}

Player::~Player(void)
{

}
