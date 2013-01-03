#include "RECTANGLE.h"

RECTANGLE::RECTANGLE(float X, float Y, float W, float H, sf::Color col)
		: x(X), y(Y), w(W), h(H), color(col)
{
	rect = sf::Shape::Rectangle(x, y, x + w, y + h, color);	
}

RECTANGLE::RECTANGLE(float X, float Y, float W, float H)
		: x(X), y(Y), w(W), h(H)
{
	sf::Color color(0, 0, 0, 255);
	rect = sf::Shape::Rectangle(x, y, x + w, y + h, color);	
}

bool RECTANGLE::contains(sf::Vector2i& point)
{
	if(point.x <= x + w && point.y <= y + h &&
	   point.x >= x     && point.y >= y)
	{
		return true;
	}
	return false;
}

void RECTANGLE::draw(sf::RenderWindow &window)
{		
	window.Draw(rect);	
}	

RECTANGLE::~RECTANGLE(void)
{

}
