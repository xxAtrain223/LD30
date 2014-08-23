#include <SFML/Graphics.hpp>
#include "GameContext.hpp"
extern GameContext *GC;

class MainGame
{
protected:
	sf::CircleShape shape;

public:
	void Initialize()
	{
		shape.setFillColor(sf::Color::Green);
		shape.setPosition(0.f, 0.f);
		shape.setRadius(100.f);
	}

	void LoadContent()
	{

	}

	void Update()
	{

	}

	void Draw()
	{
		GC->window.draw(shape);
	}
};