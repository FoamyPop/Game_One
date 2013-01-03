#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>

#include "IMAGE.h"
#include "RECTANGLE.h"
#include "STRING.h"

class BUTTON
{
public:
	BUTTON(float X, float Y, std::string text);
	~BUTTON(void);
	void Update(sf::Vector2i& mouse);
	void Draw(sf::RenderWindow &window);
	bool contains(sf::Vector2i& mouse);
	IMAGE* src;
	IMAGE* hover;
	IMAGE* reg;
	RECTANGLE* rect;
	STRING* str;
};

