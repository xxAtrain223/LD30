#include "Drawable.hpp"
#include <SFML/Graphics.hpp>

class Tile : public Drawable
{
public:
	Tile(sf::Vector2f &position, sf::Texture &texture) : Drawable(position, texture)
	{}
};
