#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC

#include <iostream>

#include <SFML/Graphics.hpp>

#include "GameContext.hpp"
#include "MainGame.hpp"

using namespace std;

GameContext *GC;

int main()
{
	GC = new GameContext();
	MainGame MG;

	GC->window.create(sf::VideoMode(1280, 800), "LD30", sf::Style::Close | sf::Style::Titlebar);

	MG.Initialize();
	MG.LoadContent();

	while (GC->window.isOpen())
	{
		sf::Event event;
		while (GC->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				GC->window.close();
			if (event.type == sf::Event::GainedFocus)
				GC->IsFocused = true;
			if (event.type == sf::Event::LostFocus)
				GC->IsFocused = false;
		}

		GC->updateKeyboard();

		if (KeyPressed(sf::Keyboard::Escape))
			GC->window.close();

		MG.Update();

		GC->window.clear(sf::Color::Blue);
		MG.Draw();
		GC->window.display();
	}

	return 0;
}