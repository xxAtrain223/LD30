#include <iostream>
#include <SFML/Graphics.hpp>

#include "GameContext.hpp"
#include "Tile.hpp"

using namespace std;

extern GameContext *GC;

class MainGame
{
protected:
	vector<vector<Tile*>> tiles;

	sf::Texture backGroundTex;
	sf::Texture foreGroundTex;

public:
	void Initialize()
	{
		
	}

	void LoadContent()
	{
		tiles = LoadLevel("level0.png");
	}

	void Update()
	{
	}

	void Draw()
	{
		for (int i = 0; i < tiles.size(); i++)
			for (int j = 0; j < tiles[i].size(); j++)
				tiles[i][j]->Draw();
	}
	
	vector<vector<Tile*>> LoadLevel(const char* filename)
	{
		sf::Color pixCol;

		vector<vector<Tile*>> tils;

		sf::Image image;
		if (!image.loadFromFile(filename)) return tils;

		if (!backGroundTex.loadFromFile("DarkBrick.png")) return tils;
		if (!foreGroundTex.loadFromFile("Brick.png")) return tils;

		tils.resize(image.getSize().x);
		for (int i = 0; i < image.getSize().x; i++)
		{
			tils[i].resize(image.getSize().y);
			for (int j = 0; j < image.getSize().y; j++)
			{
				pixCol = image.getPixel(i, j);

				if (pixCol == sf::Color::White || pixCol.a == 0)
					tils[i][j] = new Tile(sf::Vector2f(i * 64, j * 64), backGroundTex);
				else if (pixCol == sf::Color::Black)
					tils[i][j] = new Tile(sf::Vector2f(i * 64, j * 64), foreGroundTex);
			}
		}

		return tils;
	}
};


