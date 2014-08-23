#include <iostream>

#include <SFML/Graphics.hpp>

#ifndef _GAMECONTEXT_
#define _GAMECONTEXT_

#define KeyPressed(key)   GC->curKeyboard[key] && !GC->prevKeyboard[key]
#define KeyReleased(key) !GC->curKeyboard[key] &&  GC->prevKeyboard[key]
#define KeyHeld(key)      GC->curKeyboard[key]

struct GameContext
{
	sf::RenderWindow window;

	bool prevKeyboard[sf::Keyboard::KeyCount];
	bool curKeyboard[sf::Keyboard::KeyCount];

	bool IsFocused = true;

	void updateKeyboard()
	{
		if (IsFocused)
		{
			for (int i = 0; i < sf::Keyboard::KeyCount; i++)
			{
				prevKeyboard[i] = curKeyboard[i];
				curKeyboard[i] = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);
			}
		}
	}
};

#endif // !_GAMECONTEXT_
