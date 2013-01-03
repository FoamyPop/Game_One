#include "IMAGE.h"

IMAGE::IMAGE(std::string filename, float X, float Y)
{
	if(!image.LoadFromFile(filename))
	{
		std::cout << "ERROR LOADING " << filename << std::endl;
	}
	x = X;
	y = Y;
	w = image.GetWidth();
	h = image.GetHeight();
	sprite.SetImage(image);
	sprite.SetPosition(x, y);
}

void IMAGE::SetPosition(float X, float Y)
{
	x = X;
	y = Y;
	sprite.SetPosition(x, y);
}

void IMAGE::setScale(float scale)
{
	sprite.SetScale(scale, scale);
}
	
void IMAGE::draw(sf::RenderWindow& window)
{
	window.Draw(sprite);
}

IMAGE::~IMAGE(void)
{

}

