#include "BUTTON.h"

BUTTON::BUTTON(float X, float Y, std::string text)
{
	hover = new IMAGE("Images\\Hover.png", X, Y);
	reg = new IMAGE("Images\\Reg.png", X, Y);
	rect = new RECTANGLE(X, Y, reg->w, reg->h);
	src = reg;
	str = new STRING(text, X + 120, Y + 34);
}

void BUTTON::Update(sf::Vector2i& mouse)
{
	if(rect->contains(mouse))
	{
		src = hover;
	}
	else
	{
		src = reg;
	}
}

bool BUTTON::contains(sf::Vector2i& mouse)
{
	if(rect->contains(mouse))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BUTTON::Draw(sf::RenderWindow &window)
{
	src->draw(window);
	str->Draw(window);
}

BUTTON::~BUTTON(void)
{

}
