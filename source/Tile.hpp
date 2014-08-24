#include "Drawable.hpp"
#include <SFML/Graphics.hpp>

#ifndef _TILE_
#define _TILE_

class Tile : public Drawable
{
public:
	Tile(sf::Vector2f &position, sf::Texture &texture) : Drawable(position, texture)
	{}
};

#endif // !_TILE_