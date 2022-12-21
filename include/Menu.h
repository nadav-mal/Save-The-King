#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Textures.h"
#include "Sound.h"

/* The Menu class is in charge of the menu of the game.
*  The menu is displayed in a seperate window. */
class Menu
{
public:
	// C-tor
	Menu();
	void runMenu(Sound& sound); // Main function, launches the menu.
	void drawMenu(); // Draws the menu.
	void setTitle(); // Sets the title of the menu (name of the game).
	void handleClick(sf::Vector2f pos, Sound& sound); // Handles clicking on buttons of the menu.
	void pollEvents(Sound& sound); // New events handler.
	void render(); // Function to display the menu.
	void highlight(sf::Vector2i loc, Sound& sound); // Function to 'highlight' (or mark) buttons when hovered.


	/* For external-class uses. */
	sf::Sprite getMenuSprite(int place) const;
	void setHelpAndExitPos(sf::Vector2f helpPos, sf::Vector2f exitPos);

private:
	// Display management.
	sf::RenderWindow *m_menuWindow;
	sf::VideoMode m_menuVideo;
	sf::Font m_font;
	sf::Text m_text;
	std::vector<sf::Sprite> m_menuSprites;
	std::vector<sf::Sprite> m_usedSprites;
	std::vector<bool> m_reHovered;
	bool m_helpRequest;

	// For handling events.
	sf::Event m_menuEvent;

	/* Private func. */
	void initMenuWindow();
};