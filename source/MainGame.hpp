#include <iostream>
#include <SFML/Graphics.hpp>

#include "GameContext.hpp"
#include "Tile.hpp"

using namespace std;

extern GameContext *GC;

class MainGame
{
protected:
	sf::Texture tmpTexture;
	
	Tile *tile;


public:
	void Initialize()
	{
	}

	void LoadContent()
	{
		if (!tmpTexture.loadFromFile("Brick.png")) return;
		tmpTexture.setSmooth(true);
		
		tile = new Tile(sf::Vector2f(100, 100), tmpTexture);
	}

	void Update()
	{
	}

	void Draw()
	{
		tile->Draw();
	}
};


