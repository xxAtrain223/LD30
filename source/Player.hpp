#include <math.h>
#include <SFML/Graphics.hpp>
#include "Drawable.hpp"

#ifndef _PLAYER_
#define _PLAYER_

class Player : public Drawable
{
public:
	sf::Vector2f Position;
	sf::Vector2f Velocity;
	sf::Vector2f Acceleration;
	int Direction;

	sf::Texture LeftTex;
	sf::Texture RightTex;
	sf::Texture UpTex;
	sf::Texture DownTex;
	sf::Texture IdleTex;

	void Initialize(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f acc)
	{
		Position = pos;
		Velocity = vel;
		Acceleration = acc;
		Direction = 0;
	}

	void LoadContent(string left, string right, string idle)
	{
		LeftTex.loadFromFile(left);
		RightTex.loadFromFile(right);
		IdleTex.loadFromFile(idle);
	}

	void Update()
	{
		Velocity += Acceleration;
		
		if (Velocity.x < 0)
			Direction = -1;
		else if (Velocity.x > 0)
			Direction = 1;
		else
			Direction = 0;

		Sprite.setPosition(Position);
	}

	void ApplyUpdate()
	{
		Position += Velocity;
	}

	void Draw()
	{
		if (Direction == -1)
			Sprite.setTexture(LeftTex);
		else if (Direction == 0)
			Sprite.setTexture(IdleTex);
		else if (Direction == 1)
			Sprite.setTexture(RightTex);

		GC->window.draw(Sprite);
	}

	sf::IntRect Rect()
	{
		sf::IntRect rectangle = Sprite.getTextureRect();
		rectangle.top = Position.y;
		rectangle.left = Position.x;
		return rectangle;
	}
};

#endif // !_PLAYER_
