#pragma once

#include "Player.h"
#include "IMAGE.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Bullet.h"
#include "STRING.h"

class Enemy
{
public:
	Enemy(int x, int y, Player& p);
	~Enemy(void);
	void Update(sf::RenderWindow &window, std::vector<Bullet*> &bullets, Player& player);
	int getHealth()
	{
		return health;
	}
	void damage(int amount);
	void DIE(Player& player);
	bool alive;
	bool dead();
private:
	IMAGE* src;
	int health;
	STRING* display;
	int speed;
	sf::Clock timer;
	float lifetime;
};