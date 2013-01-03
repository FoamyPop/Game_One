#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class RECTANGLE
{
public:
	RECTANGLE(float X, float Y, float W, float H, sf::Color col);
	RECTANGLE(float X, float Y, float W, float H);
	bool contains(sf::Vector2i& point);
	~RECTANGLE(void);
	void draw(sf::RenderWindow &window);
private:
	sf::Shape rect;
	sf::Color color;
	float x, y, w, h;
};

