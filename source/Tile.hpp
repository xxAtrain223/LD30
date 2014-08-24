#include "Drawable.hpp"
#include <SFML/Graphics.hpp>

#ifndef _TILE_
#define _TILE_

class Tile : public Drawable
{
public:
	sf::Vector2f Position;
	bool IsSolid;

	Tile(sf::Vector2f &position, sf::Texture &texture, bool isSolid) : 
		Drawable(position, texture), IsSolid(isSolid), Position(position)
	{}

	sf::IntRect Rect()
	{
		sf::IntRect rectangle = Sprite.getTextureRect();
		rectangle.top = Position.y;
		rectangle.left = Position.x;
		return rectangle;
	}
};

#endif // !_TILE_