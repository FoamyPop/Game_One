#include "STRING.h"

STRING::STRING(std::string text, float X, float Y)
{
	if(!font.LoadFromFile("Font.ttf", 30))
	{
		std::cout << "ERROR LOADING FONT" << std::endl;
	}
	TEXT.SetFont(font);
	TEXT.SetPosition(X, Y);
	TEXT.SetColor(sf::Color(255, 180, 0));
	TEXT.SetText(text);
}

STRING::STRING(std::string text, float X, float Y, sf::Color col)
{
	if(!font.LoadFromFile("Font.ttf", 30))
	{
		std::cout << "ERROR LOADING FONT" << std::endl;
	}
	TEXT.SetFont(font);
	TEXT.SetPosition(X, Y);
	TEXT.SetColor(col);
	TEXT.SetText(text);
}

void STRING::SetText(std::string t)
{
	TEXT.SetText(t);
}

void STRING::setSize(int _Value)
{
	TEXT.SetSize(_Value);
}

void STRING::setColor(sf::Color &color)
{
	TEXT.SetColor(color);
}

void STRING::Draw(sf::RenderWindow &window)
{
	window.Draw(TEXT);
}

STRING::~STRING(void)
{

}
