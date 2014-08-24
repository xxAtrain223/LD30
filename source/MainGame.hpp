#include <iostream>
#include <SFML/Graphics.hpp>

#include "GameContext.hpp"
#include "Tile.hpp"
#include "Player.hpp"

using namespace std;

extern GameContext *GC;

class MainGame
{
protected:
	vector<vector<Tile*>> tiles;

	sf::Texture backGroundTex;
	sf::Texture foreGroundTex;

	sf::Rect<float> Camera;
	float CameraSpd = 5;

	Player Player1;
	float PlayerSpd = 3;

public:
	void Initialize()
	{
		Camera.left = 0; Camera.top = 0;
		Camera.width = GC->window.getSize().x;
		Camera.height = GC->window.getSize().y;

		Player1.Initialize(sf::Vector2f(4 * 64, 2 * 64),
						   sf::Vector2f(0, 0),
						   sf::Vector2f(0, 2));

		GC->window.setFramerateLimit(120);
	}

	void LoadContent()
	{
		tiles = LoadLevel("level0.png");
		Player1.LoadContent("PlayerLeft.png",
			                "PlayerRight.png",
							"PlayerIdle.png");
	}

	bool TestPlatCollision(sf::IntRect rect)
	{
		for (int i = 0; i < tiles.size(); i++)
			for (int j = 0; j < tiles[i].size(); j++)
				if (rect.intersects(tiles[i][j]->Rect()) && tiles[i][j]->IsSolid)
					return true;
		return false;
	}

	void UpdatePlat()
	{
		sf::IntRect PlayerRect;
		float mod;

		PlayerRect = Player1.Rect();
		PlayerRect.left += Player1.Velocity.x;
		if (TestPlatCollision(PlayerRect))
		{
			PlayerRect.left -= Player1.Velocity.x;
			mod = (Player1.Velocity.x > 0) ? 1 : ((Player1.Velocity.x < 0) ? -1 : 0);
			Player1.Velocity.x = 0;
			PlayerRect.left += mod;
			while (!TestPlatCollision(PlayerRect))
				PlayerRect.left += mod;
			PlayerRect.left -= mod;

			Player1.Position.x = PlayerRect.left;
			Player1.Sprite.setPosition(Player1.Position);
		}

		PlayerRect = Player1.Rect();
		PlayerRect.top += Player1.Velocity.y;
		if (TestPlatCollision(PlayerRect))
		{
			PlayerRect.top -= Player1.Velocity.y;
			mod = (Player1.Velocity.y > 0) ? 1 : ((Player1.Velocity.y < 0) ? -1 : 0);
			Player1.Velocity.y = 0;
			PlayerRect.top += mod;
			while (!TestPlatCollision(PlayerRect))
				PlayerRect.top += mod;
			PlayerRect.top -= mod;

			Player1.Position.y = PlayerRect.top;
			Player1.Sprite.setPosition(Player1.Position);
		}
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
				tiles[i][j]->Sprite.setPosition(tiles[i][j]->Position.x - Camera.left, tiles[i][j]->Position.y - Camera.top);

		Player1.Velocity.x = 0; Player1.Velocity.y = 0;
		if (KeyHeld(sf::Keyboard::A))
			Player1.Velocity.x -= PlayerSpd;
		if (KeyHeld(sf::Keyboard::D))
			Player1.Velocity.x += PlayerSpd;
		if (KeyHeld(sf::Keyboard::W))
			Player1.Velocity.y -= PlayerSpd;
		if (KeyHeld(sf::Keyboard::S))
			Player1.Velocity.y += PlayerSpd;

		Player1.Update();
		UpdatePlat();
		Player1.ApplyUpdate();

		Player1.Sprite.setPosition(Player1.Position.x - Camera.left, Player1.Position.y - Camera.top);
	}

	void Draw()
	{
		for (int i = 0; i < tiles.size(); i++)
			for (int j = 0; j < tiles[i].size(); j++)
				tiles[i][j]->Draw();

		Player1.Draw();
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
					tils[i][j] = new Tile(sf::Vector2f(i * 64, j * 64), backGroundTex, false);
				else if (pixCol == sf::Color::Black)
					tils[i][j] = new Tile(sf::Vector2f(i * 64, j * 64), foreGroundTex, true);
			}
		}

		return tils;
	}
};
