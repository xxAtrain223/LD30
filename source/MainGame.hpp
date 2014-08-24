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

	sf::Rect<float> Camera;
	float CameraSpd = 0.5;

public:
	void Initialize()
	{
		Camera.left = 0; Camera.top = 0;
		Camera.width = GC->window.getSize().x;
		Camera.height = GC->window.getSize().y;
	}

	void LoadContent()
	{
		tiles = LoadLevel("level0.png");
	}

	void Update()
	{
		if (KeyHeld(sf::Keyboard::Left))
			Camera.left -= CameraSpd;
		if (KeyHeld(sf::Keyboard::Right))
			Camera.left += CameraSpd;
		if (KeyHeld(sf::Keyboard::Up))
			Camera.top -= CameraSpd;
		if (KeyHeld(sf::Keyboard::Down))
			Camera.top += CameraSpd;
		if (KeyPressed(sf::Keyboard::Numpad0) || KeyPressed(sf::Keyboard::Num0))
		{
			Camera.top = 0;
			Camera.left = 0;
		}
		

		for (int i = 0; i < tiles.size(); i++)
			for (int j = 0; j < tiles[i].size(); j++)
				tiles[i][j]->Sprite.setPosition(i * 64 - Camera.left, j * 64 - Camera.top);
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


