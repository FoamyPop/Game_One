#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>

class STRING
{
public:
	STRING(std::string text, float X, float Y);
	STRING(std::string text, float X, float Y, sf::Color col);
	~STRING(void);
	sf::Font font;
	sf::String TEXT;
	void Draw(sf::RenderWindow &window);
	void SetText(std::string t);
	void setSize(int _Value);
	void setColor(sf::Color &color);
};

