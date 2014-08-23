#include <SFML/Graphics.hpp>
#include "GameContext.hpp"

extern GameContext *GC;

using namespace std;

#ifndef _DRAWABLE_
#define _DRAWABLE_

class Drawable
{
protected:
public:
	sf::IntRect Rectangle;
	sf::Sprite Sprite;

public:

	Drawable() : Sprite()
	{}

	Drawable(sf::Vector2f &position, sf::Texture &texture) : Sprite(texture)
	{
		Sprite.setPosition(position);
	}

	void SetPosition(sf::Vector2f position)
	{
		Sprite.setPosition(position);
	}

	void SetTexture(sf::Texture texture)
	{
		Sprite.setTexture(texture);
	}

	sf::Vector2i TopLeft()
	{
		Rectangle = Sprite.getTextureRect();
		return sf::Vector2i(Rectangle.left, Rectangle.top);
	}

	sf::Vector2i TopRight()
	{
		Rectangle = Sprite.getTextureRect();
		return sf::Vector2i(Rectangle.left + Rectangle.width, Rectangle.top);
	}

	sf::Vector2i BottomLeft()
	{
		Rectangle = Sprite.getTextureRect();
		return sf::Vector2i(Rectangle.left, Rectangle.top + Rectangle.height);
	}

	sf::Vector2i BottomRight()
	{
		Rectangle = Sprite.getTextureRect();
		return sf::Vector2i(Rectangle.left + Rectangle.width, Rectangle.top + Rectangle.height);
	}

	sf::Vector2i Center()
	{
		Rectangle = Sprite.getTextureRect();
		return sf::Vector2i(Rectangle.left + Rectangle.width / 2, Rectangle.top + Rectangle.height / 2);
	}

	sf::IntRect Rect()
	{
		Rectangle = Sprite.getTextureRect();
		return Rectangle;
	}

	void Draw()
	{
		GC->window.draw(Sprite);
	}
};

#endif // !_DRAWABLE_
