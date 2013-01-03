#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Player.h"
#include <cstdlib>

class Bullet
{
public:
	Bullet(int DIRECTION, Player& player);
	~Bullet(void);
	void Update(sf::RenderWindow &window);
	IMAGE* src;
	int direction;
	int speed;
	bool alive;
	int rnd;
	enum DIRECTIONS
	{
		UP, DOWN, LEFT, RIGHT
	};
};

