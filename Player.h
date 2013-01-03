#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "IMAGE.h"

class Player
{
public:
	Player(int x, int y);
	~Player(void);
	void Draw(sf::RenderWindow &window);
	int health;
	int armour;
	bool move[4];
	int speed;	
	int SCORE;
	void damage(int value);
	void Update();
	IMAGE* src;
};
